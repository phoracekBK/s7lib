#include <s7lib.h>
#include <snap7.h>

struct _s7lib_
{
	S7Object Client;

	char * IPAddress;
	int Rack;
	int Slot;
	int DB_index;

	uint8_t connection_try;
};

typedef struct _s7lib_ s7lib;




s7lib * s7lib_new(char * IPAddress, int Rack, int Slot, int DB_index)
{
	s7lib * this = malloc(sizeof(s7lib));

	this->Client = Cli_Create();

	this->IPAddress = c_string_init(IPAddress);
	this->Rack = Rack;
	this->Slot = Slot;
	this->DB_index = DB_index;

	this->connection_try = 0;

	if(s7lib_connect(this) == true)
		printf("connected\n");
	else
		printf("connection error\n");

	return this;
}


bool s7lib_connect(s7lib * this)
{
	if(Cli_ConnectTo(this->Client, this->IPAddress, this->Rack, this->Slot) == 0)
		return true;
	else
		return false;
}

bool s7lib_disconnect(s7lib * this)
{
	if(Cli_Disconnect(this->Client) == 0)
		return true;
	else
		return false;
}


void s7lib_finalize(s7lib * this)
{
	s7lib_disconnect(this);
	Cli_Destroy(&(this->Client));

	free(this->IPAddress);

	free(this);
}


bool s7lib_reconnect(s7lib * this, uint8_t connection_try)
{
	if(connection_try < 3)
	{
		s7lib_disconnect(this);

		if(s7lib_connect(this) == true)
		{
			return true;
		}
		else
		{
			usleep(50000);
			return s7lib_reconnect(this, connection_try + 1);
		}
	}

	return false;
}

uint8_t * s7lib_read(s7lib * this, int base, int size)
{
	uint8_t * byte_array = malloc(sizeof(uint8_t)*size);

	if(Cli_DBRead(this->Client, this->DB_index, base, size, byte_array) != 0)
	{
		free(byte_array);
		s7lib_reconnect(this, 0);

		return NULL;
	}

	return byte_array;
}

bool s7lib_write(s7lib * this, uint8_t * byte_array, int base, int size)
{
	uint8_t * s7lib_byte_array = s7lib_read(this, base, size);

	if((s7lib_byte_array != NULL) && (byte_array != NULL))
	{
		if(memcmp(s7lib_byte_array, byte_array, size) != 0)
		{
			if(Cli_DBWrite(this->Client, this->DB_index, base, size, byte_array) != 0)
			{
				return false;
			}
			else
			{
				free(s7lib_byte_array);
				usleep(50000);
				return s7lib_write(this, byte_array, base, size);
			}
		}

		free(s7lib_byte_array);
		return true;
	}

	return false;
}


bool s7lib_read_bool(s7lib * this, int byte_index, int bit_index)
{
	uint8_t * byte = s7lib_read(this, byte_index, 1);

	if(byte != NULL)
	{
		bool cmd = s7lib_parser_read_bool(byte, 0, bit_index);

		free(byte);

		return cmd;
	}

	return false;
}

bool s7lib_write_bool(s7lib * this, int byte_index, int bit_index, bool value)
{
	uint8_t * byte = s7lib_read(this, byte_index, 1);

	if(byte != NULL)
	{
		bool ret_val = s7lib_write(this,  s7lib_parser_write_bool(byte, 0, bit_index, value), byte_index, 1);

		free(byte);

		return ret_val;
	}

	return false;
}

int16_t s7lib_read_int(s7lib * this, int byte_index)
{
	uint8_t * byte_array = s7lib_read(this, byte_index, 2);

	if(byte_array != NULL)
		return s7lib_parser_read_int(byte_array, 0);

	return 0;
}

bool s7lib_write_int(s7lib * this, int byte_index, int16_t value)
{
	uint8_t * byte_array = malloc(sizeof(uint8_t)*2);

	bool ret_val = s7lib_write(this, s7lib_parser_write_int(byte_array, 0, value), byte_index, 2);

	free(byte_array);

	return ret_val;
}

bool s7lib_write_dword(s7lib * this, int byte_index, int32_t value)
{
	uint8_t * byte_array = malloc(sizeof(uint8_t)*4);

	bool ret_val = s7lib_write(this,  s7lib_parser_write_dword(byte_array, byte_index, value), byte_index, 4);

	free(byte_array);

	return ret_val;
}

uint32_t s7lib_read_dword(s7lib * this, int byte_index)
{
	uint8_t * byte_array = s7lib_read(this, byte_index, 4);

	if(byte_array != NULL)
	{
		uint32_t value = s7lib_parser_read_dword(byte_array, byte_index);

		free(byte_array);

		return value;
	}

	return 0;
}

bool s7lib_write_real(s7lib *this, int byte_index, float value)
{
  uint8_t * byte_array = malloc(sizeof(uint8_t)*4);

  bool ret_val = s7lib_write(this, s7lib_parser_write_real(byte_array, 0, value), byte_index, 4);

  free(byte_array);

  return ret_val;
}

float s7lib_read_real(s7lib * this, int byte_index)
{
  uint8_t * byte_array = s7lib_read(this, byte_index, 4);

  if(byte_array != NULL)
  {
    float value = s7lib_parser_read_real(byte_array, 0);

    free(byte_array);

    return value;
  }

  return 0;
}

bool s7lib_write_string(s7lib * this, int byte_index, char * string, uint8_t size)
{
	uint8_t * byte_array = malloc(sizeof(uint8_t)*(size+2));

	bool ret_val = s7lib_write(this, s7lib_parser_write_string(byte_array, 0, string, size), byte_index, size+2);

	free(byte_array);

	return ret_val;
}

char * s7lib_read_string(s7lib * this, int byte_index, uint8_t size)
{
	uint8_t * byte_array = s7lib_read(this, byte_index, size);

	if(byte_array != NULL)
	{
		char * string = s7lib_parser_read_string(byte_array, 0, size);

		free(byte_array);

		return string;
	}

	return NULL;
}
