#include <stdio.h>
#include <string.h>

//xml namespace mapping and gsoap glue code
#include "CountriesPortSoap11.nsmap"
char wsdl_path[512];
int http_get(struct soap *soap) {
	FILE *fd = NULL;
	char *s = strchr(soap->path, '?');
	if (!s || strcmp(s, "?wsdl"))
		return SOAP_GET_METHOD;
	fd = fopen(wsdl_path, "rb"); // open WSDL file to copy
	if (!fd)
		return 404; // return HTTP not found error
	soap->http_content = "text/xml"; // HTTP header with text/xml content
	soap_response(soap, SOAP_FILE);
	for (;;) {
		size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
		if (!r)
			break;
		if (soap_send_raw(soap, soap->tmpbuf, r))
			break; // can't send, but little we can do about that
	}
	fclose(fd);
	soap_end_send(soap);
	return SOAP_OK;
}

int main(int argc, char** argv) {
	int m, s; /* master and slave sockets */
	struct soap *soap = soap_new();
	soap->fget = http_get;
	if (argc < 3) {
		printf("usage: port_number wsdl_path");
		exit(-1);
	} else {
		strcpy(wsdl_path, argv[2]);
		m = soap_bind(soap, NULL, atoi(argv[1]), 100); /* bind to the port supplied as command-line argument */
		if (m < 0) {
			soap_print_fault(soap, stderr);
			exit(-1);
		}
		fprintf(stderr, "Socket connection successful: master socket = %d\n",
				m);
		for (;;) {
			s = soap_accept(soap);
			fprintf(stderr, "Socket connection successful: slave socket = %d\n",
					s);
			if (s < 0) {
				soap_print_fault(soap, stderr);
				exit(1);
			}
			soap_serve(soap);
			soap_end(soap);
		}
	}
	soap_done(soap);
	free(soap);
	return 0;
}


int __ns1__getCountry(struct soap* soap,
		struct _ns1__getCountryRequest *ns1__getCountryRequest,
		struct _ns1__getCountryResponse *ns1__getCountryResponse) {

	printf("@@@%s", ns1__getCountryRequest->name);
	ns1__getCountryResponse->country=malloc(sizeof(struct ns1__country));
	ns1__getCountryResponse->country->population = 1235;

	return SOAP_OK;
}

