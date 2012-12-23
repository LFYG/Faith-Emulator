#include "msgaccount.h"
#include "client.h"
#include "server.h"
#include "msgconnect.h"
#include <string>
#include <string.h>

using namespace std;

MsgAccount :: MsgAccount(const char* aAccount, const char* aPassword, const char* aServer)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aAccount, aPassword, aServer);
}

MsgAccount :: MsgAccount(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgAccount :: ~MsgAccount()
{

}

void
MsgAccount :: create(const char* aAccount, const char* aPassword, const char* aServer)
{
    ASSERT(aAccount != nullptr && aAccount[0] != '\0');
    ASSERT(aPassword != nullptr && aPassword[0] != '\0');
    ASSERT(aServer != nullptr && aServer[0] != '\0');

    if (strlen(aAccount) < MAX_NAMESIZE &&
            strlen(aPassword) < MAX_NAMESIZE &&
            strlen(aServer) < MAX_NAMESIZE)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_ACCOUNT;

        strcpy(mInfo->Account, aAccount);
        // TODO: Encrypt password
        strcpy(mInfo->Password, aPassword);
        strcpy(mInfo->Server, aServer);
    }
    else
    {
        LOG("Invalid length: account=%zu, password=%zu, server=%zu",
               strlen(aAccount), strlen(aPassword), strlen(aServer));
    }
}

void
MsgAccount :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    aClient->setAccount(mInfo->Account);

    if (true) // Database.Authenticate
    {
        fprintf(stdout, "Connection of %s on %s...\n",
                mInfo->Account, mInfo->Server);

        // FIXME !
        int32_t accUID = 1;
        int32_t token = 1;

        MsgConnect msg(accUID, token, Server::SERVER_IP);
        aClient->send(&msg);
    }
    else
    {
        // Bruteforce protection
        // send bad password packet
    }
}