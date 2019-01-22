/* soapStub.h
   Generated by gSOAP 2.8.22 from foxlinkadd.h

Copyright(C) 2000-2015, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_ns1	"http://tempuri.org/Imports"
#define SOAP_NAMESPACE_OF_tempuri	"http://tempuri.org/"
#include "stdsoap2.h"
#if GSOAP_VERSION != 20822
# error "GSOAP VERSION 20822 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE__tempuri__CheckRuleSN
#define SOAP_TYPE__tempuri__CheckRuleSN (8)
/* tempuri:CheckRuleSN */
class SOAP_CMAC _tempuri__CheckRuleSN
{
public:
	std::string *TPART_USCORENO;	/* optional element of type xsd:string */
	std::string *TSN;	/* optional element of type xsd:string */
	std::string *TTYPE;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique type id SOAP_TYPE__tempuri__CheckRuleSN */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__CheckRuleSN() { _tempuri__CheckRuleSN::soap_default(NULL); }
	virtual ~_tempuri__CheckRuleSN() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__CheckRuleSNResponse
#define SOAP_TYPE__tempuri__CheckRuleSNResponse (9)
/* tempuri:CheckRuleSNResponse */
class SOAP_CMAC _tempuri__CheckRuleSNResponse
{
public:
	std::string *CheckRuleSNResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 9; } /* = unique type id SOAP_TYPE__tempuri__CheckRuleSNResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__CheckRuleSNResponse() { _tempuri__CheckRuleSNResponse::soap_default(NULL); }
	virtual ~_tempuri__CheckRuleSNResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__COMMAND_USCORECODE
#define SOAP_TYPE__tempuri__COMMAND_USCORECODE (10)
/* tempuri:COMMAND_CODE */
class SOAP_CMAC _tempuri__COMMAND_USCORECODE
{
public:
	std::string *CMD1;	/* optional element of type xsd:string */
	std::string *CMD2;	/* optional element of type xsd:string */
	std::string *CMD3;	/* optional element of type xsd:string */
	std::string *CMD4;	/* optional element of type xsd:string */
	std::string *CMD5;	/* optional element of type xsd:string */
	std::string *CMD6;	/* optional element of type xsd:string */
	std::string *CMD7;	/* optional element of type xsd:string */
	std::string *TSTATION;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 10; } /* = unique type id SOAP_TYPE__tempuri__COMMAND_USCORECODE */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__COMMAND_USCORECODE() { _tempuri__COMMAND_USCORECODE::soap_default(NULL); }
	virtual ~_tempuri__COMMAND_USCORECODE() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__COMMAND_USCORECODEResponse
#define SOAP_TYPE__tempuri__COMMAND_USCORECODEResponse (11)
/* tempuri:COMMAND_CODEResponse */
class SOAP_CMAC _tempuri__COMMAND_USCORECODEResponse
{
public:
	std::string *COMMAND_USCORECODEResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 11; } /* = unique type id SOAP_TYPE__tempuri__COMMAND_USCORECODEResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__COMMAND_USCORECODEResponse() { _tempuri__COMMAND_USCORECODEResponse::soap_default(NULL); }
	virtual ~_tempuri__COMMAND_USCORECODEResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__UpdateSMTSteelNet
#define SOAP_TYPE__tempuri__UpdateSMTSteelNet (12)
/* tempuri:UpdateSMTSteelNet */
class SOAP_CMAC _tempuri__UpdateSMTSteelNet
{
public:
	std::string *strMO;	/* optional element of type xsd:string */
	int *intLINECODE;	/* optional element of type xsd:int */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 12; } /* = unique type id SOAP_TYPE__tempuri__UpdateSMTSteelNet */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__UpdateSMTSteelNet() { _tempuri__UpdateSMTSteelNet::soap_default(NULL); }
	virtual ~_tempuri__UpdateSMTSteelNet() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__UpdateSMTSteelNetResponse
#define SOAP_TYPE__tempuri__UpdateSMTSteelNetResponse (13)
/* tempuri:UpdateSMTSteelNetResponse */
class SOAP_CMAC _tempuri__UpdateSMTSteelNetResponse
{
public:
	std::string *UpdateSMTSteelNetResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 13; } /* = unique type id SOAP_TYPE__tempuri__UpdateSMTSteelNetResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__UpdateSMTSteelNetResponse() { _tempuri__UpdateSMTSteelNetResponse::soap_default(NULL); }
	virtual ~_tempuri__UpdateSMTSteelNetResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__UpdateSMTSteelNet2
#define SOAP_TYPE__tempuri__UpdateSMTSteelNet2 (14)
/* tempuri:UpdateSMTSteelNet2 */
class SOAP_CMAC _tempuri__UpdateSMTSteelNet2
{
public:
	std::string *strMO;	/* optional element of type xsd:string */
	int *intLINECODE;	/* optional element of type xsd:int */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 14; } /* = unique type id SOAP_TYPE__tempuri__UpdateSMTSteelNet2 */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__UpdateSMTSteelNet2() { _tempuri__UpdateSMTSteelNet2::soap_default(NULL); }
	virtual ~_tempuri__UpdateSMTSteelNet2() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__UpdateSMTSteelNet2Response
#define SOAP_TYPE__tempuri__UpdateSMTSteelNet2Response (15)
/* tempuri:UpdateSMTSteelNet2Response */
class SOAP_CMAC _tempuri__UpdateSMTSteelNet2Response
{
public:
	std::string *UpdateSMTSteelNet2Result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 15; } /* = unique type id SOAP_TYPE__tempuri__UpdateSMTSteelNet2Response */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__UpdateSMTSteelNet2Response() { _tempuri__UpdateSMTSteelNet2Response::soap_default(NULL); }
	virtual ~_tempuri__UpdateSMTSteelNet2Response() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__BatchBack
#define SOAP_TYPE__tempuri__BatchBack (16)
/* tempuri:BatchBack */
class SOAP_CMAC _tempuri__BatchBack
{
public:
	std::string *strQA_USCORENO;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 16; } /* = unique type id SOAP_TYPE__tempuri__BatchBack */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__BatchBack() { _tempuri__BatchBack::soap_default(NULL); }
	virtual ~_tempuri__BatchBack() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__BatchBackResponse
#define SOAP_TYPE__tempuri__BatchBackResponse (17)
/* tempuri:BatchBackResponse */
class SOAP_CMAC _tempuri__BatchBackResponse
{
public:
	std::string *BatchBackResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 17; } /* = unique type id SOAP_TYPE__tempuri__BatchBackResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__BatchBackResponse() { _tempuri__BatchBackResponse::soap_default(NULL); }
	virtual ~_tempuri__BatchBackResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__saveSingleReworkResult
#define SOAP_TYPE__tempuri__saveSingleReworkResult (18)
/* tempuri:saveSingleReworkResult */
class SOAP_CMAC _tempuri__saveSingleReworkResult
{
public:
	std::string *strEMP_USCORENO;	/* optional element of type xsd:string */
	int *intSTART_USCOREGROUP_USCORECODE;	/* optional element of type xsd:int */
	std::string *strECN_USCOREMEMO;	/* optional element of type xsd:string */
	std::string *strSERIAL_USCORENUMBER;	/* optional element of type xsd:string */
	std::string *strVERSION_USCORECODE;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 18; } /* = unique type id SOAP_TYPE__tempuri__saveSingleReworkResult */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__saveSingleReworkResult() { _tempuri__saveSingleReworkResult::soap_default(NULL); }
	virtual ~_tempuri__saveSingleReworkResult() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__saveSingleReworkResultResponse
#define SOAP_TYPE__tempuri__saveSingleReworkResultResponse (19)
/* tempuri:saveSingleReworkResultResponse */
class SOAP_CMAC _tempuri__saveSingleReworkResultResponse
{
public:
	std::string *saveSingleReworkResultResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 19; } /* = unique type id SOAP_TYPE__tempuri__saveSingleReworkResultResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__saveSingleReworkResultResponse() { _tempuri__saveSingleReworkResultResponse::soap_default(NULL); }
	virtual ~_tempuri__saveSingleReworkResultResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__Check_USCORELogin
#define SOAP_TYPE__tempuri__Check_USCORELogin (20)
/* tempuri:Check_Login */
class SOAP_CMAC _tempuri__Check_USCORELogin
{
public:
	std::string *strUser;	/* optional element of type xsd:string */
	std::string *strPwd;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 20; } /* = unique type id SOAP_TYPE__tempuri__Check_USCORELogin */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__Check_USCORELogin() { _tempuri__Check_USCORELogin::soap_default(NULL); }
	virtual ~_tempuri__Check_USCORELogin() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__Check_USCORELoginResponse
#define SOAP_TYPE__tempuri__Check_USCORELoginResponse (21)
/* tempuri:Check_LoginResponse */
class SOAP_CMAC _tempuri__Check_USCORELoginResponse
{
public:
	std::string *Check_USCORELoginResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 21; } /* = unique type id SOAP_TYPE__tempuri__Check_USCORELoginResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__Check_USCORELoginResponse() { _tempuri__Check_USCORELoginResponse::soap_default(NULL); }
	virtual ~_tempuri__Check_USCORELoginResponse() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__SaveTestData
#define SOAP_TYPE__tempuri__SaveTestData (22)
/* tempuri:SaveTestData */
class SOAP_CMAC _tempuri__SaveTestData
{
public:
	std::string *strData;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 22; } /* = unique type id SOAP_TYPE__tempuri__SaveTestData */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__SaveTestData() { _tempuri__SaveTestData::soap_default(NULL); }
	virtual ~_tempuri__SaveTestData() { }
};
#endif

#ifndef SOAP_TYPE__tempuri__SaveTestDataResponse
#define SOAP_TYPE__tempuri__SaveTestDataResponse (23)
/* tempuri:SaveTestDataResponse */
class SOAP_CMAC _tempuri__SaveTestDataResponse
{
public:
	std::string *SaveTestDataResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 23; } /* = unique type id SOAP_TYPE__tempuri__SaveTestDataResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _tempuri__SaveTestDataResponse() { _tempuri__SaveTestDataResponse::soap_default(NULL); }
	virtual ~_tempuri__SaveTestDataResponse() { }
};
#endif

#ifndef SOAP_TYPE___tempuri__CheckRuleSN
#define SOAP_TYPE___tempuri__CheckRuleSN (31)
/* Operation wrapper: */
struct __tempuri__CheckRuleSN
{
public:
	_tempuri__CheckRuleSN *tempuri__CheckRuleSN;	/* optional element of type tempuri:CheckRuleSN */
public:
	int soap_type() const { return 31; } /* = unique type id SOAP_TYPE___tempuri__CheckRuleSN */
};
#endif

#ifndef SOAP_TYPE___tempuri__COMMAND_USCORECODE
#define SOAP_TYPE___tempuri__COMMAND_USCORECODE (35)
/* Operation wrapper: */
struct __tempuri__COMMAND_USCORECODE
{
public:
	_tempuri__COMMAND_USCORECODE *tempuri__COMMAND_USCORECODE;	/* optional element of type tempuri:COMMAND_CODE */
public:
	int soap_type() const { return 35; } /* = unique type id SOAP_TYPE___tempuri__COMMAND_USCORECODE */
};
#endif

#ifndef SOAP_TYPE___tempuri__UpdateSMTSteelNet
#define SOAP_TYPE___tempuri__UpdateSMTSteelNet (39)
/* Operation wrapper: */
struct __tempuri__UpdateSMTSteelNet
{
public:
	_tempuri__UpdateSMTSteelNet *tempuri__UpdateSMTSteelNet;	/* optional element of type tempuri:UpdateSMTSteelNet */
public:
	int soap_type() const { return 39; } /* = unique type id SOAP_TYPE___tempuri__UpdateSMTSteelNet */
};
#endif

#ifndef SOAP_TYPE___tempuri__UpdateSMTSteelNet2
#define SOAP_TYPE___tempuri__UpdateSMTSteelNet2 (43)
/* Operation wrapper: */
struct __tempuri__UpdateSMTSteelNet2
{
public:
	_tempuri__UpdateSMTSteelNet2 *tempuri__UpdateSMTSteelNet2;	/* optional element of type tempuri:UpdateSMTSteelNet2 */
public:
	int soap_type() const { return 43; } /* = unique type id SOAP_TYPE___tempuri__UpdateSMTSteelNet2 */
};
#endif

#ifndef SOAP_TYPE___tempuri__BatchBack
#define SOAP_TYPE___tempuri__BatchBack (47)
/* Operation wrapper: */
struct __tempuri__BatchBack
{
public:
	_tempuri__BatchBack *tempuri__BatchBack;	/* optional element of type tempuri:BatchBack */
public:
	int soap_type() const { return 47; } /* = unique type id SOAP_TYPE___tempuri__BatchBack */
};
#endif

#ifndef SOAP_TYPE___tempuri__saveSingleReworkResult
#define SOAP_TYPE___tempuri__saveSingleReworkResult (51)
/* Operation wrapper: */
struct __tempuri__saveSingleReworkResult
{
public:
	_tempuri__saveSingleReworkResult *tempuri__saveSingleReworkResult;	/* optional element of type tempuri:saveSingleReworkResult */
public:
	int soap_type() const { return 51; } /* = unique type id SOAP_TYPE___tempuri__saveSingleReworkResult */
};
#endif

#ifndef SOAP_TYPE___tempuri__Check_USCORELogin
#define SOAP_TYPE___tempuri__Check_USCORELogin (55)
/* Operation wrapper: */
struct __tempuri__Check_USCORELogin
{
public:
	_tempuri__Check_USCORELogin *tempuri__Check_USCORELogin;	/* optional element of type tempuri:Check_Login */
public:
	int soap_type() const { return 55; } /* = unique type id SOAP_TYPE___tempuri__Check_USCORELogin */
};
#endif

#ifndef SOAP_TYPE___tempuri__SaveTestData
#define SOAP_TYPE___tempuri__SaveTestData (59)
/* Operation wrapper: */
struct __tempuri__SaveTestData
{
public:
	_tempuri__SaveTestData *tempuri__SaveTestData;	/* optional element of type tempuri:SaveTestData */
public:
	int soap_type() const { return 59; } /* = unique type id SOAP_TYPE___tempuri__SaveTestData */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (60)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 60; } /* = unique type id SOAP_TYPE_SOAP_ENV__Header */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (61)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 61; } /* = unique type id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (63)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 63; } /* = unique type id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (66)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 66; } /* = unique type id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (67)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
public:
	int soap_type() const { return 67; } /* = unique type id SOAP_TYPE_SOAP_ENV__Fault */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */
