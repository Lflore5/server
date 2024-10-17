/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include "declarations.hpp"
#include "lib/logging/log_with_spd_log.hpp"

#ifndef USE_PRECOMPILED_HEADERS
	#include <mutex>
#endif

#include <mysqlx/xdevapi.h>

class DBResult;
class PreparedStatement;

using DBResult_ptr = std::shared_ptr<DBResult>;

class Database {
private:
	std::unique_ptr<mysqlx::Session> m_databaseSession;

public:
	static const size_t MAX_QUERY_SIZE = 8 * 1024 * 1024; // 8 Mb -- half the default MySQL max_allowed_packet size

	Database() = default;
	~Database();

	// Singleton - ensures we don't accidentally copy it.
	Database(const Database &) = delete;
	Database &operator=(const Database &) = delete;

	static Database &getInstance();

	bool connect();

	bool connect(const std::string* host, const std::string* user, const std::string* password, const std::string* database, uint32_t port, const std::string* sock);

	bool retryQuery(const std::string &query, int retries);
	bool executeQuery(const std::string &query);

	DBResult_ptr storeQuery(std::string_view query);
	std::shared_ptr<DBResult> prepare(const std::string &query);

	std::unique_ptr<mysqlx::SqlResult> getResult(std::string_view query);

	std::string escapeString(const std::string &s) const;

	std::string escapeBlob(const char* s, uint32_t length) const;

	/**
	 * @brief Updates blob data in a specified column and table.
	 *
	 * This method updates a BLOB column in a specified table using a provided blob of data. It logs
	 * the number of affected rows or any errors encountered during the update.
	 *
	 * @param tableName Name of the table to update.
	 * @param columnName Name of the BLOB column to update.
	 * @param recordId ID of the record to update.
	 * @param blobData Pointer to the blob data to be updated.
	 * @param size Size of the blob data.
	 * @param idColumnName Name of the column used as the identifier.
	 * @return true if the update is successful, false otherwise.
	 */
	bool updateBlobData(const std::string &tableName, const std::string &columnName, uint32_t recordId, const char* blobData, size_t size, const std::string &idColumnName = "id");

	/**
	 * @brief Inserts data into a specified table.
	 *
	 * This method inserts a new row into a table with specified columns and values. It checks and logs
	 * the number of affected rows to ensure that the insert operation was successful.
	 *
	 * @param tableName Name of the table where data will be inserted.
	 * @param columns Vector of strings containing the names of the columns to insert data into.
	 * @param values Vector of mysqlx::Value containing the data to be inserted.
	 * @return true if the insert is successful, false otherwise.
	 */
	bool insertTable(const std::string &tableName, const std::vector<std::string> &columns, const std::vector<mysqlx::Value> &values);

	/**
	 * @brief Updates or inserts data into a table based on the existence of a record.
	 *
	 * This method checks if a record exists and updates it. If the record does not exist, it inserts a new record.
	 * The method logs actions taken (update or insert) and any errors encountered.
	 *
	 * @param tableName Name of the table to update.
	 * @param columns Names of the columns to update.
	 * @param values Values corresponding to the columns.
	 * @param whereColumnName The column name used in the WHERE clause to locate the record.
	 * @param whereValue The value used in the WHERE clause to locate the record.
	 * @return true if the operation was successful, false otherwise.
	 */
	bool updateTable(const std::string &tableName, const std::vector<std::string> &columns, const std::vector<mysqlx::Value> &values, const std::vector<std::string> &whereColumnNames, const std::vector<mysqlx::Value> &whereValues);

	/**
	 * @brief Updates or inserts data into a table based on complex WHERE conditions.
	 *
	 * This method performs an update or insert operation based on complex WHERE conditions specified by multiple columns.
	 * It handles both single and multiple records and logs detailed information about the operations and any exceptions.
	 *
	 * @param tableName Name of the table to update or insert into.
	 * @param columns Vector of column names to be updated or inserted.
	 * @param values Vector of values corresponding to the columns.
	 * @param whereColumnNames Vector of column names used for the WHERE clause to locate the record.
	 * @param whereValues Vector of values used for the WHERE clause to locate the record.
	 * @return true if the update or insert is successful, false otherwise.
	 */
	bool updateTable(const std::string &tableName, const std::vector<std::string> &columns, const std::vector<mysqlx::Value> &values, const std::string &whereColumnName, const mysqlx::Value &whereValue);

	uint64_t getMaxPacketSize() const {
		return maxPacketSize;
	}

	bool isValidSession() const;
	mysqlx::Session &getSession();
	mysqlx::Schema getDatabaseSchema();

	mysqlx::Table getTable(const std::string &tableName);

	bool transactionalExecute(std::function<bool(Database &)> transactionFunc);

	static uint8_t getU8(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static uint16_t getU16(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static uint32_t getU32(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static uint64_t getU64(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static int8_t getI8(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static int16_t getI16(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static int32_t getI32(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static int64_t getI64(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static double getDouble(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static float getFloat(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static bool getBool(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());
	static std::string getString(const mysqlx::Value &val, const std::source_location &location = std::source_location::current());

private:
	bool beginTransaction();
	bool rollback();
	bool commit();

	std::recursive_mutex databaseLock;
	uint64_t maxPacketSize = 1048576;

	friend class DBTransaction;
};

constexpr auto g_database = Database::getInstance;

class DBResult {
public:
	explicit DBResult(mysqlx::SqlResult &&result, std::string_view query, mysqlx::Session &session);
	explicit DBResult(mysqlx::Session &session, const std::string &query);

	~DBResult();

	// Non copyable
	DBResult(const DBResult &) = delete;
	DBResult &operator=(const DBResult &) = delete;

	template <typename... Args>
	bool executeWithParams(Args &&... args) {
		try {
			mysqlx::SqlStatement stmt = m_session.sql(m_query);
			(stmt.bind(std::forward<Args>(args)), ...);
			m_result = stmt.execute();
			m_currentRow = m_result.fetchOne();
			if (m_currentRow.isNull()) {
				g_logger().debug("[{}] no results for query: {}", __FUNCTION__, m_query);
				return false;
			}
			m_hasMoreRows = !m_currentRow.isNull();
			initializeColumnMap();
			return true;
		} catch (const mysqlx::Error &err) {
			g_logger().error("PreparedStatement error with MySQL X DevAPI: {}", err.what());
			return false;
		} catch (const std::exception &e) {
			g_logger().error("PreparedStatement execute error: {}", e.what());
			;
			return false;
		}
	}

	uint8_t getU8(std::string_view columnName) const;
	uint16_t getU16(std::string_view columnName) const;
	uint32_t getU32(std::string_view columnName) const;
	uint64_t getU64(std::string_view columnName) const;

	int8_t getI8(std::string_view columnName) const;
	int16_t getI16(std::string_view columnName) const;
	int32_t getI32(std::string_view columnName) const;
	int64_t getI64(std::string_view columnName) const;

	time_t getTime(std::string_view columnName) const;
	float getFloat(std::string_view columnName) const;
	double getDouble(std::string_view columnName) const;
	bool getBool(std::string_view columnName) const;

	std::string getString(const std::string &columnName) const;
	const std::vector<uint8_t> getStream(const std::string &columnName) const;

	size_t countResults() const;
	bool hasNext() const;
	bool next();

private:
	void initializeColumnMap();

	mysqlx::Session &m_session;
	std::string m_query;
	mysqlx::SqlResult m_result;
	mysqlx::Row m_currentRow;
	mysqlx::col_count_t m_columnCount;
	mysqlx::row_count_t m_resultCount;

	std::unordered_map<std::string, size_t> listNames;
	bool m_hasMoreRows = false;

	friend class Database;
};

/**
 * INSERT statement.
 */
class DBInsert {
public:
	explicit DBInsert(const std::string &query);
	void upsert(const std::vector<std::string> &columns);
	bool addRow(std::string_view row);
	bool addRow(std::ostringstream &row);
	bool execute();

private:
	std::vector<std::string> upsertColumns;
	std::string query;
	std::string values;
	size_t length;
};

class DBTransaction {
public:
	explicit DBTransaction() = default;

	~DBTransaction() = default;

	// non-copyable
	DBTransaction(const DBTransaction &) = delete;
	DBTransaction &operator=(const DBTransaction &) = delete;

	// non-movable
	DBTransaction(const DBTransaction &&) = delete;
	DBTransaction &operator=(const DBTransaction &&) = delete;

	template <typename Func>
	static bool executeWithinTransaction(const Func &toBeExecuted) {
		DBTransaction transaction;
		try {
			transaction.begin();
			bool result = toBeExecuted();
			transaction.commit();
			return result;
		} catch (const std::exception &exception) {
			transaction.rollback();
			g_logger().error("[{}] Error occurred committing transaction, error: {}", __FUNCTION__, exception.what());
			return false;
		}
	}

private:
	bool begin() {
		// Ensure that the transaction has not already been started
		if (state != STATE_NO_START) {
			return false;
		}

		try {
			// Start the transaction
			state = STATE_START;
			return g_database().beginTransaction();
		} catch (const std::exception &exception) {
			// An error occurred while starting the transaction
			state = STATE_NO_START;
			g_logger().error("[{}] An error occurred while starting the transaction, error: {}", __FUNCTION__, exception.what());
			return false;
		}
	}

	void rollback() {
		// Ensure that the transaction has been started
		if (state != STATE_START) {
			return;
		}

		try {
			// Rollback the transaction
			state = STATE_NO_START;
			g_database().rollback();
		} catch (const std::exception &exception) {
			// An error occurred while rolling back the transaction
			g_logger().error("[{}] An error occurred while rolling back the transaction, error: {}", __FUNCTION__, exception.what());
		}
	}

	void commit() {
		// Ensure that the transaction has been started
		if (state != STATE_START) {
			g_logger().error("Transaction not started");
			return;
		}

		try {
			// Commit the transaction
			state = STATE_COMMIT;
			g_database().commit();
		} catch (const std::exception &exception) {
			// An error occurred while committing the transaction
			state = STATE_NO_START;
			g_logger().error("[{}] An error occurred while committing the transaction, error: {}", __FUNCTION__, exception.what());
		}
	}

	bool isStarted() const {
		return state == STATE_START;
	}
	bool isCommitted() const {
		return state == STATE_COMMIT;
	}
	bool isRolledBack() const {
		return state == STATE_NO_START;
	}

	TransactionStates_t state = STATE_NO_START;
};

class DatabaseException : public std::exception {
public:
	explicit DatabaseException(const std::string &message) :
		message(message) { }

	virtual const char* what() const throw() {
		return message.c_str();
	}

private:
	std::string message;
};
