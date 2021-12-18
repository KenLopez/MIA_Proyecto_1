use IDADB;

CREATE TABLE countrycodes(
    id int auto_increment not null,
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
    name_wb_code varchar(20),
    primary key(id)
);

CREATE TABLE status(
    id int auto_increment not null,
    name varchar(100),
    primary key(id)
);

CREATE TABLE currency(
    id int auto_increment not null,
    name varchar(100),
    primary key(id)
);

CREATE TABLE locations(
    id int auto_increment not null,
    location_type_code varchar(20),
    location_type_name varchar(100),
    primary key(id)
);

CREATE TABLE project(
    id int auto_increment not null,
    project_id varchar(50),
    is_geocoded bit(1),
    project_title varchar(100),
    start_actual_isodate date,
    end_actual_isodate date,
    donors varchar(50),
    donors_iso3 varchar(20),
    recipients int,
    recipients_iso3 varchar(20),
    ad_sector_code varchar(50),
    ad_sector_names varchar(100),
    status int,
    transactions_start_year smallint,
    transactions_end_year smallint, 
    total_commitments float,
    total_disbursements float,
    primary key(id),
    foreign key (recipients) references countrycodes(id),
    foreign key (status) references status(id)
);

CREATE TABLE geoname(
    id int auto_increment not null,
    geoname_id int,
    place_name varchar(50),
    latitude float,
    longitude float,
    location_type_code int,
    location_type_name varchar(100),
    gazetteer_adm_code varchar(100),
    gazetteer_adm_name varchar(100),
    location_class smallint,
    geografic_exactness smallint,
    primary key(id),
    foreign key (location_type_code) references locations(id)
);

CREATE TABLE level(
    id int auto_increment not null,
    project_id int,
    project_location_id varchar(100),
    geoname_id int,
    transactions_start_year smallint,
    transactions_end_year smallint,
    even_split_commitments float,
    even_split_disbursements float,
    primary key(id),
    foreign key (project_id) references project(id),
    foreign key (geoname_id) references geoname(id)
);

CREATE TABLE transaction(
    id int auto_increment not null,
    transactions_id varchar(50),
    project_id int,
    transaction_isodate date,
    transaction_year smallint,
    transaction_value_code char(1),
    transaction_currency int,
    transaction_value float,
    primary key(id),
    foreign key (project_id) references project(id),
    foreign key (transaction_currency) references currency(id)
);