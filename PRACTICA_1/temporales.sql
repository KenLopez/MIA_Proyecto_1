use IDADB;

CREATE TABLE temp_country_codes(
    name varchar(100),
    iso2 varchar(20),
    name_name varchar(100),
    name_aiddata_code int,
    name_aiddata_name varchar(100),
    name_cow_alpha varchar(20),
    name_cow_numeric smallint,
    name_fao_code smallint,
    name_fips varchar(20),
    name_geonames_id int,
    name_imf_code smallint,
    name_iso2 varchar(20),
    name_iso3 varchar(20),
    name_iso_numeric smallint,
    name_oecd_code smallint,
    name_oecd_name varchar(100),
    name_un_code smallint,
    name_wb_code varchar(20)
);

CREATE TABLE temp_geonames(
    geoname_id int,
    place_name varchar(50),
    latitude float,
    longitude float,
    location_type_code varchar(100),
    location_type_name varchar(100),
    gazetteer_adm_code varchar(100),
    gazetteer_adm_name varchar(100),
    location_class smallint,
    geografic_exactness smallint
);

CREATE TABLE temp_level_1a(
    project_id varchar(50),
    project_location_id varchar(100),
    geoname_id int,
    transactions_start_year smallint,
    transactions_end_year smallint,
    even_split_commitments float,
    even_split_disbursements float
);

CREATE TABLE temp_locations(
    location_type_code varchar(20),
    location_type_name varchar(100)
);

CREATE TABLE temp_projects(
    project_id varchar(50),
    is_geocoded int,
    project_title varchar(100),
    start_actual_isodate varchar(10),
    end_actual_isodate varchar(10),
    donors varchar(50),
    donors_iso3 varchar(20),
    recipients varchar(100),
    recipients_iso3 varchar(20),
    ad_sector_code varchar(50),
    ad_sector_names varchar(100),
    status varchar(100),
    transactions_start_year smallint,
    transactions_end_year smallint, 
    total_commitments float,
    total_disbursements float
);

CREATE TABLE temp_transactions(
    transactions_id varchar(50),
    project_id varchar(50),
    transaction_isodate varchar(10),
    transaction_year smallint,
    transaction_value_code varchar(1),
    transaction_currency varchar(100),
    transaction_value float
);