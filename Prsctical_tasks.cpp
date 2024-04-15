#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <list>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std; 




namespace TCP {
	enum class EVENT {
		APP_PASSIVE_OPEN,
		APP_ACTIVE_OPEN,
		APP_SEND,
		APP_CLOSE,
		APP_TIMEOUT,
		RCV_SYN,
		RCV_ACK,
		RCV_SYN_ACK,
		RCV_FIN,
		RCV_FIN_ACK
	};

	enum class STATE {
		CLOSED,
		LISTEN,
		SYN_SENT,
		SYN_RCVD,
		ESTABLISHED,
		CLOSE_WAIT,
		LAST_ACK,
		FIN_WAIT_1,
		FIN_WAIT_2,
		CLOSING,
		TIME_WAIT
	};

	std::multimap<STATE, std::map<EVENT, STATE>> stateEvents{
		{CLOSED, {
			{EVENT::APP_PASSIVE_OPEN, STATE::LISTEN},
			{EVENT::APP_ACTIVE_OPEN, STATE::SYN_SENT}
		} },
		{LISTEN, {
			{EVENT::RCV_SYN, STATE::SYN_RCVD},
			{EVENT::APP_SEND, STATE::SYN_SENT},
			{EVENT::APP_CLOSE, STATE::CLOSED}
		} },
		{SYN_SENT, {
			{EVENT::RCV_SYN, STATE::SYN_RCVD},
			{EVENT::RCV_SYN_ACK, STATE::ESTABLISHED},
			{EVENT::APP_CLOSE, STATE::CLOSED}
		} },
		{SYN_RCVD, {
			{EVENT::APP_CLOSE, STATE::FIN_WAIT_1},
			{EVENT::RCV_ACK, STATE::ESTABLISHED}
		} },
		{ESTABLISHED, {
			{EVENT::APP_CLOSE, STATE::FIN_WAIT_1},
			{EVENT::RCV_FIN, STATE::CLOSE_WAIT}
		} },
		{CLOSE_WAIT, {
			{EVENT::APP_CLOSE, STATE::LAST_ACK}
		} },
		{LAST_ACK, {
			{EVENT::RCV_ACK, STATE::CLOSED}
		} },
		{FIN_WAIT_1, {
			{EVENT::RCV_FIN, STATE::CLOSING},
			{EVENT::RCV_FIN_ACK, STATE::TIME_WAIT},
			{EVENT::RCV_ACK, STATE::FIN_WAIT_2}
		} },
		{FIN_WAIT_2, {
			{EVENT::RCV_FIN, STATE::TIME_WAIT}
		} },
		{CLOSING, {
			{EVENT::RCV_ACK, STATE::TIME_WAIT}
		} },
		{TIME_WAIT, {
			{EVENT::APP_TIMEOUT, STATE::CLOSED}
		} }
	};
}





int main() {
	string initial = "CLOSED";
	cout << "Enter the initial state: ";
	cin >> initial;
	string event;
	cout << "Enter the event: ";
	cin >> event;
	string final;
	cout << "Enter the final state: ";
	cin >> final;

	if (TCP::stateEvents[initial] == make_pair<EVENT, STATE>(event, final) &&
		TCP::stateEvents[FINAL_STATE] == EVENT) {
		cout << "The transition is valid" << endl;
	}
	else {
		cout << "The transition is invalid" << endl;
	}

	return 0;
}




		



