#define DHT11_PIN RB0

typedef struct{
    char Humidity_integer;
    char Humidity_decimal;
    char Temperature_integer;
    char Temperature_decimal;
    char Check_sum;
}DHT11_type;

void DHT11_request(void);
void DHT11_response(void);
char DHT11_receive(void);
void DHT11_read(void);
