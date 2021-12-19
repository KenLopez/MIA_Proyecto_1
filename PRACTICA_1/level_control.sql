use IDADB;

LOAD DATA LOCAL INFILE './ArchivosCSV/level_1a.csv' INTO TABLE IDADB.temp_level_1a COLUMNS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES (project_id, project_location_id, geoname_id, transactions_start_year, transactions_end_year, even_split_commitments, even_split_disbursements);