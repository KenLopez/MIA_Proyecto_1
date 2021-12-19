use IDADB;

LOAD DATA LOCAL INFILE './ArchivosCSV/geonames.csv' INTO TABLE IDADB.temp_geonames COLUMNS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES (geoname_id, place_name, latitude, longitude, location_type_code, location_type_name, gazetteer_adm_code, gazetteer_adm_name, location_class, geografic_exactness);