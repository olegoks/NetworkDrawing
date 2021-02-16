#pragma once
#ifndef PACKET_HPP
#define PACKET_HPP

#include "ServerTypes.hpp"

using PacketSize = unsigned long long;

EXPIMP class Packet {
private:

	PacketSize size_;
	Byte* usefull_data_;

public:

	EXPIMP explicit CALLBACK Packet(const PacketSize packet_size)noexcept(true);
	EXPIMP explicit CALLBACK Packet(const PacketSize packet_size, const Byte* const data)noexcept(true);
	EXPIMP explicit CALLBACK Packet()noexcept(true);

	EXPIMP CALLBACK Packet(Packet&& packet)noexcept(true);
	EXPIMP CALLBACK Packet(const Packet& packet)noexcept(true);
	EXPIMP const PacketSize CALLBACK Size()const noexcept(true);
	EXPIMP const Byte* CALLBACK Data()const noexcept(true);
	EXPIMP Byte* CALLBACK Data()noexcept(true);
	EXPIMP Packet& CALLBACK operator=(Packet&& packet)noexcept(true);
	EXPIMP Packet& CALLBACK operator=(const Packet& packet)noexcept(true);
	EXPIMP bool CALLBACK operator==(const Packet& packet)const noexcept(true);

	EXPIMP CALLBACK ~Packet()noexcept(false);

};

#endif //PACKET_HPP