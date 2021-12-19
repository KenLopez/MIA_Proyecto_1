use IDADB;

INSERT INTO status (
    name
)
SELECT DISTINCT status FROM temp_projects;

INSERT INTO currency(
    name
)
SELECT DISTINCT transaction_currency FROM temp_transactions;

INSERT INTO locations(
    location_type_code,
    location_type_name
)
SELECT location_type_code, location_type_name FROM temp_locations;

INSERT INTO countrycodes(
    name,
    iso2,
    name_name, 
    name_aiddata_code,
    name_aiddata_name,
    name_cow_alpha,
    name_cow_numeric,
    name_fao_code,
    name_fips, 
    name_geonames_id,
    name_imf_code,
    name_iso2,
    name_iso3,
    name_iso_numeric,
    name_oecd_code,
    name_oecd_name,
    name_un_code,
    name_wb_code
)
SELECT 
    name,
    iso2,
    name_name, 
    name_aiddata_code,
    name_aiddata_name,
    name_cow_alpha,
    name_cow_numeric,
    name_fao_code,
    name_fips, 
    name_geonames_id,
    name_imf_code,
    name_iso2,
    name_iso3,
    name_iso_numeric,
    name_oecd_code,
    name_oecd_name,
    name_un_code,
    name_wb_code
FROM temp_country_codes;

INSERT INTO geoname(
    geoname_id,
    place_name,
    latitude,
    longitude,
    location_type_code,
    location_type_name,
    gazetteer_adm_code,
    gazetteer_adm_name,
    location_class,
    geografic_exactness
)
SELECT
    geoname_id,
    place_name,
    latitude,
    longitude,
    locations.id,
    temp_geonames.location_type_name,
    gazetteer_adm_code,
    gazetteer_adm_name,
    location_class,
    geografic_exactness
FROM temp_geonames, locations
WHERE locations.location_type_code = temp_geonames.location_type_code;

INSERT INTO project(
    project_id,
    is_geocoded,
    project_title,
    start_actual_isodate,
    end_actual_isodate,
    donors,
    donors_iso3,
    recipients,
    recipients_iso3,
    ad_sector_code,
    ad_sector_names,
    status,
    transactions_start_year,
    transactions_end_year,
    total_commitments,
    total_disbursements
)
SELECT DISTINCT 
    project_id,
    is_geocoded,
    project_title,
    STR_TO_DATE(start_actual_isodate, "%d/%m/%Y"),
    if(end_actual_isodate = '', NULL, STR_TO_DATE(end_actual_isodate, "%d/%m/%Y")),
    donors,
    donors_iso3,
    countrycodes.id,
    recipients_iso3,
    ad_sector_code,
    ad_sector_names,
    status.id,
    transactions_start_year,
    transactions_end_year,
    total_commitments,
    total_disbursements
FROM temp_projects, status, countrycodes
WHERE status.name = temp_projects.status
AND (countrycodes.name = temp_projects.recipients
OR countrycodes.name_iso3 = temp_projects.recipients_iso3);

DELETE t1 FROM project t1
INNER JOIN project t2 
WHERE 
    t1.id < t2.id AND 
    t1.project_id = t2.project_id;

INSERT INTO level(
    project_id,
    project_location_id,
    geoname_id,
    transactions_start_year,
    transactions_end_year,
    even_split_commitments,
    even_split_disbursements
)
SELECT DISTINCT
    project.id,
    project_location_id,
    geoname.id,
    temp_level_1a.transactions_start_year,
    temp_level_1a.transactions_end_year,
    even_split_commitments,
    even_split_disbursements
FROM temp_level_1a, project, geoname
WHERE project.project_id = temp_level_1a.project_id
AND geoname.geoname_id = temp_level_1a.geoname_id;

DELETE t1 FROM level t1
INNER JOIN level t2 
WHERE 
    t1.id < t2.id 
    AND t1.geoname_id = t2.geoname_id;

INSERT INTO transaction(
    transactions_id,
    project_id,
    transaction_isodate,
    transaction_year,
    transaction_value_code,
    transaction_currency,
    transaction_value
)
SELECT 
    transactions_id,
    project.id,
    if(transaction_isodate = '', NULL, STR_TO_DATE(transaction_isodate, "%d/%m/%Y")),
    transaction_year,
    transaction_value_code,
    currency.id,
    transaction_value
FROM temp_transactions, project, currency
WHERE project.project_id = temp_transactions.project_id
AND currency.name = temp_transactions.transaction_currency;

