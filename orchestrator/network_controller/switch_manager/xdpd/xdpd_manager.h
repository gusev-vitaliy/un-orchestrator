#ifndef XDPDManager_H_
#define XDPDManager_ 1

#pragma once

#include "../switch_manager.h"

#include "../../../utils/constants.h"
#include "../../../utils/sockutils.h"
#include "../../../utils/logger.h"

#include "xdpd_constants.h"

#include <json_spirit/json_spirit.h>
#include <json_spirit/value.h>
#include <json_spirit/writer.h>

#include <string>
#include <list>
#include <sstream>

using namespace std;
using namespace json_spirit;

class LSI;

class XDPDManager : public SwitchManager
{
private:
	/**
	*	@brief: remote TCP port to be used to send commands to xDPd
	*/
	string xDPDport;

	/**
	*	@brief: keeps the addrinfo chain; required to open a new socket
	*/
	struct addrinfo *AddrInfo;
	
	/**
	*	@brief: Send a message to xDPD
	*
	*	@param: message	Message to be sent
	*/
	string sendMessage(string message);
	
	string prepareCreateLSIrequest(CreateLsiIn cli);
	CreateLsiOut *parseCreateLSIresponse(CreateLsiIn cli, Object message);
	
	string prepareDestroyLSIrequest(uint64_t dpid);
	void parseDestroyLSIresponse(Object message);
	
	string prepareCreateVirtualLinkRequest(AddVirtualLinkIn avli);
	AddVirtualLinkOut *parseCreateVirtualLinkResponse(AddVirtualLinkIn avli, Object message);
	
	string prepareDestroyVirtualLinkRequest(DestroyVirtualLinkIn dvli);
	void parseDestroyVirtualLinkResponse(Object message);
	
	string prepareCreateNFPortsRequest(AddNFportsIn anpi);
	AddNFportsOut *parseCreateNFPortsResponse(AddNFportsIn anpi, Object message);
	
	string prepareDestroyNFPortsRequest(DestroyNFportsIn dnpi);
	void parseDestroyNFPortsResponse(Object message);
	
	bool findCommand(Object message, string expected);
	bool findStatus(Object message);

public:
	XDPDManager();

	~XDPDManager();

	/**
	*	@brief: Cretes a new LSI in xDPD
	*
	*	@param: lsi		Description of the LSI
	*					to be created
	*/
	CreateLsiOut *createLsi(CreateLsiIn cli);

	/**
	*	@brief: Create NF ports of a specific NF on an LSI in xDPD
	*
	*	@brief: lsi		Description of the LSI containing the
	*					NF ports to be created
	*	@brief: nf		Name and port idendifiers of the NF whose ports must be created
	*	@brief: type	Type of the NF associated with the ports to be created
	*/
	AddNFportsOut *addNFPorts(AddNFportsIn anpi);

	/**
	*	@brief: Destroy add a virtual link to an LSI in xDPDP
	*
	*	@param: lsi		Description of the LSI containing the vlink
	*					to be added
	*	@param: vlink	Structure representing the virtual link to
	*					to be added to the LSI
	*/
	AddVirtualLinkOut *addVirtualLink(AddVirtualLinkIn avli);

	/**
	*	@brief: Destroy an existing LSI in xDPD
	*
	*	@param: lsi		Description of the LSI
	*					to be destroyed
	*/
	void destroyLsi(uint64_t dpid);

	/**
	*	@brief: Destroy all the NF ports of a specific NF
	*
	*	@brief: lsi		Description of the LSI containing the
	*					NF ports to be removed
	*	@brief: nf		Name of the NF whose ports must be removed
	*/
	void destroyNFPorts(DestroyNFportsIn dnpi);

	/**
	*	@brief: Destroy an virtual link from an LSI in xDPDP
	*
	*	@param: lsi		Description of the LSI containing the vlink
	*					to be removed
	*	@param: vlinkID	Identifier of the vlink to be removed
	*/
	void destroyVirtualLink(DestroyVirtualLinkIn dvli); 

	/**
	*	@brief: Connect to xDPD to discover the physical interfaces
	*/
	map<string,string> discoverEthernetInterfaces();
};

class XDPDManagerException: public SwitchManagerException
{
public:
	virtual const char* what() const throw()
	{
		return "xDPDManagerException";
	}
};

#endif //XDPDManager_H_
