#include <stdio.h>
#include <string.h>

//xml namespace mapping and gsoap glue code
#include "CountriesPortSoap11.nsmap"

int main(int argc, char** argv) {

	//create soap environement
	struct soap *soap = soap_new();

	//create request and response
	struct _ns1__getCountryRequest req;
	struct _ns1__getCountryResponse res;

	//fill the request with the name of the country
	char* name = "Poland";
	req.name = malloc((sizeof(char)) * (strlen(name) + 1));
	strcpy(req.name, name);

	if (soap_call___ns1__getCountry(soap, NULL, NULL, &req, &res) == SOAP_OK)
		//ok! response properly filled
		printf("Population: %d", res.country->population);
	else
		soap_print_fault(soap, stderr);

	//cleanup
	free(req.name);
	soap_free(soap);
	return 1;
}
