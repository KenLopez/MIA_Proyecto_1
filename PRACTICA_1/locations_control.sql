use IDADB;

LOAD DATA LOCAL INFILE './ArchivosCSV/locations.csv' INTO TABLE IDADB.temp_locations COLUMNS TERMINATED BY '\t' LINES TERMINATED BY '\n' IGNORE 1 LINES (location_type_code, location_type_name);