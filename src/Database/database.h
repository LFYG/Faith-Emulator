/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_DATABASE_H_
#define _FAITH_EMULATOR_DATABASE_H_

#include "common.h"
#include <QtSql/QSqlDatabase>

class QSqlQuery;
class Player;

/**
 * The global database class for interation with the SQL-like database.
 * It is a singleton and will be created when getting the instance.
 */
class Database
{
    // the database can manipulate the Player data...
    friend class Player;

public:
    /**
     * Get the Database singleton. If the object does not exist yet,
     * it will be created.
     *
     * @returns A reference to the singleton
     */
    static Database& getInstance();

public:
    /* destructor */
    ~Database();

    /**
     * Establish a connection to the host using the specified account.
     *
     * @param[in]   aHost        the IP address or the DNS of the host
     * @param[in]   aDbName      the database name
     * @param[in]   aUserName    the account name
     * @param[in]   aPassword    the password of the account
     *
     * @retval TRUE on success
     * @returns FALSE otherwise
     */
    bool connect(const char* aHost, const char* aDbName,
                 const char* aUserName, const char* aPassword);

    /**
     * Authenticate the account/password pair sent by a client.
     *
     * @param[in]   aAccount    the account name
     * @param[in]   aPassword   the password of the account
     *
     * @retval ERROR_SUCCESS on success
     * @retval ERROR_EXEC_FAILED if the SQL cmd failed
     * @retval ERROR_NOT_FOUND if the account/password pair was not found
     * @returns Error code otherwise
     */
    err_t authenticate(const char* aAccount, const char* aPassword);

private:
    /* constructor */
    Database();

private:
    static Database* sInstance; //!< static instance of the singleton

private:
    QSqlDatabase mConnection; //!< SQL connection for the queries
};

#endif // _FAITH_EMULATOR_DATABASE_H_