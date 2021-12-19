use IDADB;

LOAD DATA LOCAL INFILE './ArchivosCSV/projects.csv' INTO TABLE IDADB.temp_projects CHARACTER SET latin1 COLUMNS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES (project_id, is_geocoded, project_title, start_actual_isodate, end_actual_isodate, donors, donors_iso3, recipients, recipients_iso3, ad_sector_code, ad_sector_names, status, transactions_start_year, transactions_end_year, total_commitments, total_disbursements);