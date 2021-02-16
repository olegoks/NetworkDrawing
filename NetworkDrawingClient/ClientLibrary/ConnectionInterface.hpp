#pragma once
#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <functional>
#include <string>
#include <any>

#include "Packet.hpp"

extern class ConnectionInterface;

using ProcessConnectionPacketsFunction = std::function<void(ConnectionInterface, Packet)>;
using ProcessConnectionFunction = std::function<void(ConnectionInterface)>;

EXPIMP class ConnectionInterface{
private:

	std::any implementation_;

public:

	EXPIMP explicit CALLBACK ConnectionInterface(const std::any implementation)noexcept(true);
	EXPIMP error_code CALLBACK SendPacket(const Packet* const packet) const noexcept(true);
	EXPIMP Port CALLBACK Port()const noexcept(true);
	EXPIMP std::string CALLBACK Ip()const noexcept(true);
	EXPIMP bool CALLBACK IsProcessing()const noexcept(true);

};

#endif //CONNECTION_HPP