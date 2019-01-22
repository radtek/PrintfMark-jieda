#include <iostream>
#include <locale>
#include <codecvt>
#include "stdsoap2.h"
#include "soapBasicHttpBinding_USCOREIFoxlinkAddService.h"
#include "BasicHttpBinding_USCOREIFoxlinkAdd.nsmap"


int main(int argc, char* argv[])
{
	BasicHttpBinding_USCOREIFoxlinkAddService c(SOAP_C_UTFSTRING);
	struct soap* soap = c.soap;
	soap_bind(soap, NULL, 18083, 100);
	while(1)
	{
		soap_accept(soap);
		{
			if (soap_begin_serve(soap))
			{
				soap_stream_fault(soap, std::cout);
			}
			else if (c.dispatch() == SOAP_NO_METHOD)
			{
				soap_stream_fault(soap, std::cout);
			}
		}
		soap_destroy(soap);
		soap_end(soap);
	}
	soap_free(soap);
	return 0;
}


/// Web service operation 'CheckRuleSN' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::CheckRuleSN(_tempuri__CheckRuleSN *tempuri__CheckRuleSN, _tempuri__CheckRuleSNResponse &tempuri__CheckRuleSNResponse)
{
	return SOAP_OK;
}

/// Web service operation 'COMMAND_CODE' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::COMMAND_USCORECODE(_tempuri__COMMAND_USCORECODE *tempuri__COMMAND_USCORECODE, _tempuri__COMMAND_USCORECODEResponse &tempuri__COMMAND_USCORECODEResponse) 
{
	return SOAP_OK;
}

/// Web service operation 'UpdateSMTSteelNet' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::UpdateSMTSteelNet(_tempuri__UpdateSMTSteelNet *tempuri__UpdateSMTSteelNet, _tempuri__UpdateSMTSteelNetResponse &tempuri__UpdateSMTSteelNetResponse)
{
	return SOAP_OK;
}
/// Web service operation 'UpdateSMTSteelNet2' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::UpdateSMTSteelNet2(_tempuri__UpdateSMTSteelNet2 *tempuri__UpdateSMTSteelNet2, _tempuri__UpdateSMTSteelNet2Response &tempuri__UpdateSMTSteelNet2Response)
{
	return SOAP_OK;
}

/// Web service operation 'BatchBack' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::BatchBack(_tempuri__BatchBack *tempuri__BatchBack, _tempuri__BatchBackResponse &tempuri__BatchBackResponse)
{
	return SOAP_OK;
}

/// Web service operation 'saveSingleReworkResult' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::saveSingleReworkResult(_tempuri__saveSingleReworkResult *tempuri__saveSingleReworkResult, _tempuri__saveSingleReworkResultResponse &tempuri__saveSingleReworkResultResponse) 
{
	return SOAP_OK;
}

/// Web service operation 'Check_Login' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::Check_USCORELogin(_tempuri__Check_USCORELogin *tempuri__Check_USCORELogin, _tempuri__Check_USCORELoginResponse &tempuri__Check_USCORELoginResponse)
{
	return SOAP_OK;
}

/// Web service operation 'SaveTestData' (returns error code or SOAP_OK)
int BasicHttpBinding_USCOREIFoxlinkAddService::SaveTestData(_tempuri__SaveTestData *tempuri__SaveTestData, _tempuri__SaveTestDataResponse &tempuri__SaveTestDataResponse) 
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	tempuri__SaveTestDataResponse.SaveTestDataResult = new std::string;
	*tempuri__SaveTestDataResponse.SaveTestDataResult = conv.to_bytes(L"OK;行為正確完成");
	std::cout << *tempuri__SaveTestDataResponse.SaveTestDataResult << std::endl;
	return SOAP_OK;
}
