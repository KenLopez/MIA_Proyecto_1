SELECT count(start_actual_isodate) AS "Proyectos iniciados en 2011" 
FROM project 
WHERE YEAR(start_actual_isodate) = 2011;

SELECT 
    project_id AS "Codigo de proyecto", 
    project_title AS "Titulo de proyecto", 
    datediff(end_actual_isodate,start_actual_isodate) AS "Duracion" 
FROM project 
ORDER BY duracion DESC LIMIT 1;

SELECT 
    project_id AS "Codigo de proyecto", 
    project_title AS "Titulo de proyecto", 
    datediff(end_actual_isodate,start_actual_isodate) AS "Duracion" 
FROM project 
WHERE end_actual_isodate IS NOT NULL ORDER BY "Duracion" ASC LIMIT 1;

SELECT 
    countrycodes.name AS "Pais", 
    count(recipients) AS "Cantidad" 
FROM 
    project, 
    countrycodes 
WHERE project.recipients = countrycodes.id 
GROUP BY recipients 
ORDER BY 2 DESC LIMIT 5;

SELECT 
    countrycodes.name AS "Pais", 
    count(recipients) AS "Cantidad" 
FROM 
    project, 
    countrycodes 
WHERE project.recipients = countrycodes.id 
GROUP BY recipients 
ORDER BY 2 ASC LIMIT 5;

SELECT
    transaction.id,
    transactions_id,
    transaction.project_id,
    (select project_title from project where project_id = transaction.project_id),
    transaction_isodate,
    transaction_year,
    transaction_value_code,
    (select name from currency where currency.id = transaction.transaction_currency),
    transaction_value
FROM
    transaction,
    currency,
    project;

SELECT
    transaction.id,
    transactions_id,
    transaction.project_id,
    project.project_title
    transaction_isodate,
    transaction_year,
    transaction_value_code,
    currency.name,
    transaction_value
FROM
    transaction,
    currency,
    project;
WHERE
    transaction.project_id = project.id
    AND project.project_title like "%RI-East Africa Public Health Laboratory Networking Project%"
    AND currency.id = transaction.transaction_currency
ORDER BY
    transaction.transaction_value DESC LIMIT 3;