use IDADB;

CREATE TABLE temp_country_codes(
    name varchar(100),
    iso2 varchar(20),
    name_name varchar(100),
    name_aiddata_code varchar(50),
    name_aiddata_name varchar(100),
    name_cow_alpha varchar(20),
    name_cow_numeric varchar(50),
    name_fao_code varchar(50),
    name_fips varchar(20),
    name_geonames_id varchar(100),
    name_imf_code varchar(50),
    name_iso2 varchar(20),
    name_iso3 varchar(20),
    name_iso_numeric varchar(50),
    name_oecd_code varchar(50),
    name_oecd_name varchar(100),
    name_un_code varchar(50),
    name_wb_code varchar(20)
);

CREATE TABLE temp_geonames(
    geoname_id varchar(100),
    place_name varchar(50),
    latitude varchar(50),
    longitude varchar(50),
    location_type_code varchar(20),
    location_type_name varchar(100),
    gazetteer_adm_code varchar(100),
    gazetteer_adm_name varchar(100),
    location_class varchar(50),
    geografic_exactness varchar(50)
);

CREATE TABLE temp_level_1a(
    project_id varchar(50),
    project_location_id varchar(100),
    geoname_id varchar(50),
    transactions_start_year varchar(50),
    transactions_end_year varchar(50),
    even_split_commitments varchar(50),
    even_split_disbursements varchar(50)
);

CREATE TABLE temp_locations(
    location_type_code varchar(20),
    location_type_name varchar(100)
);

CREATE TABLE temp_projects(
    project_id varchar(50),
    is_geocoded varchar(5),
    project_title varchar(100),
    start_actual_isodate varchar(10),
    end_actual_isodate varchar(10),
    donors varchar(50),
    donors_iso3 varchar(20),
    recipients varchar(50),
    recipients_iso3 varchar(20),
    ad_sector_code varchar(50),
    ad_sector_names varchar(100),
    status varchar(50),
    transactions_start_year varchar(50),
    transactions_end_year varchar(50), 
    total_commitments varchar(50),
    total_disbursements varchar(50)
);

CREATE TABLE temp_transactions(
    transactions_id varchar(50),
    project_id varchar(20),
    transaction_isodate varchar(10),
    transaction_year varchar(50),
    transaction_value_code varchar(5),
    transaction_currency varchar(10),
    transaction_value varchar(50)
);