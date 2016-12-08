//
// Created by dialight on 31.10.16.
//
#include "network/properties/PropertiesClient.hpp"
#include <Properties.hpp>
#include <network/exceptions/IOException.hpp>
#include <network/properties/protocol/in/ChangePropertyPacket.hpp>
#include <network/properties/protocol/in/PingPacket.hpp>
#include <network/properties/protocol/in/GetAllPropertiesPacket.hpp>
#include <network/properties/protocol/in/GetPropertyPacket.hpp>
#include <network/properties/protocol/in/ResetPropertyPacket.hpp>
#include <network/properties/protocol/out/AddPropertyPacket.hpp>
#include <network/properties/protocol/out/RemovePropertyPacket.hpp>
#include <network/properties/protocol/out/PongPacket.hpp>
#include <network/properties/protocol/out/AllPropertiesPacket.hpp>

using namespace std;

bool PropertiesClient::DEBUG = false;
vector<PacketType> PropertiesClient::IGNORE_PACKET = {PacketType::PING, PacketType::PONG};

PropertiesClient::PropertiesClient(ServerAddr *addr) : TCPPacketClient() {
    this->addr = addr;
    this->clientThread = NULL;
    props.registerListener(this);
}

void PropertiesClient::onNewProperty(std::string name, PropertyPointer property) {
    AddPropertyPacket pa(name, property);
    trySendPacket(&pa);
}

PropertiesClient::~PropertiesClient() {
    if(clientThread != NULL) {
        close();
        clientThread->join();
        delete clientThread;
    }
}

//int PropertiesClient::getInt(const string& name, int defVal) {
//    auto it = props.find(name);
//    if (it != props.end()) return ((IntProperty *) it->second)->get();
//    PropertyPointer prop = new IntProperty(defVal);
//    props.insert(pair<string, PropertyPointer>(name, prop));
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
//    return defVal;
//}
//
//double PropertiesClient::getDouble(const string& name, double defVal) {
//    auto it = props.find(name);
//    if (it != props.end()) return ((DoubleProperty *) it->second)->get();
//    PropertyPointer prop = new DoubleProperty(defVal);
//    props.insert(pair<string, PropertyPointer>(name, prop));
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
//    return defVal;
//}
//
//int PropertiesClient::getSelect(const string &name, map<int, string> *values, int defVal) {
//    auto it = props.find(name);
//    if (it != props.end()) return ((SelectProperty *) it->second)->getSelected();
//    PropertyPointer prop = new SelectProperty(values, defVal);
//    props.insert(pair<string, PropertyPointer>(name, prop));
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
//    return defVal;
//}

void PropertiesClient::runAsync() {
    clientThread = new thread(connectStatic, this);
}

void PropertiesClient::connect() {

    Protocol protocol;

    protocol.registerInPacket(0, GetAllPropertiesPacket::constructor);
    protocol.registerInPacket(1, GetPropertyPacket::constructor);
    protocol.registerInPacket(2, ChangePropertyPacket::constructor);
    protocol.registerInPacket(3, ResetPropertyPacket::constructor);
    protocol.registerInPacket(0xFF, PingPacket::constructor);

    setProtocol(&protocol);

    registerInPacketHandler(onInPacketReceivedStatic, this);
    registerOutPacketHandler(onOutPacketSendStatic, this);

    try {
        while(alive) {
            try {
                ConnectionGuard guard(this, addr); //life cycle safe
                while (alive && isConnected()) {
                    processPacket();
                }
                //guard destructor close connection
            } catch(IOException e) {
                e.printError();
            }
            if(!alive) break;
            cond.wait(2);
        }
    } catch (RuntimeException e) {
        e.printError();
        alive = false;
    }
    cout << "Exit PropertiesClient thread gracefully" << endl;
}

template <typename T>
bool contains(vector<T> list, T x) {
    for (auto it = list.begin(); it != list.end(); ++it)
        if (*it == x) return true;
    return false;
}

void PropertiesClient::onOutPacketSend(OutPacket *p) {
    if(DEBUG && !contains(IGNORE_PACKET, p->getType())) {
        cout << "Out packet(id=" << p->getId() << "): " << p->toString() << endl;
    }
}

void PropertiesClient::onInPacketReceived(InPacket *p) {
    if(DEBUG && !contains(IGNORE_PACKET, p->getType())) {
        cout << "In packet(id=" << p->getId() << "): " << p->toString() << endl;
    }
    switch (p->getType()) {
        case GET_ALL_PROPERTIES: {
            AllPropertiesPacket pa(&props.all);
            sendPacket(&pa);
        }break;
        case GET_PROPERTY: {
            GetPropertyPacket *packet = (GetPropertyPacket *) p;
            PropertyPointer prop = props.getProperty(packet->key);
            if (prop != nullptr) {
                AddPropertyPacket pa(packet->key, prop);
                sendPacket(&pa);
            } else {
                RemovePropertyPacket pa(packet->key);
                sendPacket(&pa);
            }
        }break;
        case CHANGE_PROPERTY: {
            ChangePropertyPacket *packet = (ChangePropertyPacket *) p;
            auto it = props.all.find(packet->key);
            if (it != props.all.end()) {
                if(it->second->getType() != packet->value->getType()) {
                    throw new RuntimeException("Wrong type of property: " + packet->value->getType());
                }
                it->second->updateFrom(packet->value);
            } else {
                props.all.insert(pair<string, PropertyPointer>(packet->key, packet->value));
            }
        }break;
        case RESET_PROPERTY: {
            ResetPropertyPacket *packet = (ResetPropertyPacket *) p;
            props.all.erase(packet->key);
        }break;
        case PING: {
            PingPacket *packet = (PingPacket *) p;
            PongPacket pa(packet->time);
            sendPacket(&pa);
        }break;
        default:
            cerr << "Unhandled packet id: " << p->getId() << endl;
            break;
    }
}


