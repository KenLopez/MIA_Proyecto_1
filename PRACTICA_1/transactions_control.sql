use IDADB;

LOAD DATA LOCAL INFILE './ArchivosCSV/transactions.csv' INTO TABLE IDADB.temp_transactions COLUMNS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES (transactions_id, project_id, transaction_isodate, transaction_year, transaction_value_code, transaction_currency, transaction_value);