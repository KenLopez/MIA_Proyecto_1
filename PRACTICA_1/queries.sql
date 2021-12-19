/*PRIMERA CONSULTA*/
SELECT count(start_actual_isodate) AS "Proyectos iniciados en 2011" 
FROM project 
WHERE YEAR(start_actual_isodate) = 2011;

/*SEGUNDA CONSULTA*/
SELECT 
    project_id AS "Codigo de proyecto", 
    project_title AS "Titulo de proyecto", 
    datediff(end_actual_isodate,start_actual_isodate) AS "Duracion" 
FROM project 
ORDER BY duracion DESC LIMIT 1;

/*TERCERA CONSULTA*/
SELECT 
    project_id AS "Codigo de proyecto", 
    project_title AS "Titulo de proyecto", 
    datediff(end_actual_isodate,start_actual_isodate) AS "Duracion" 
FROM project 
WHERE end_actual_isodate IS NOT NULL ORDER BY "Duracion" ASC LIMIT 1;

/*CUARTA CONSULTA*/
SELECT 
    countrycodes.name AS "Pais", 
    count(recipients) AS "Cantidad" 
FROM 
    project, 
    countrycodes 
WHERE project.recipients = countrycodes.id 
GROUP BY recipients 
ORDER BY 2 DESC LIMIT 5;

/*QUINTA CONSULTA*/
SELECT 
    countrycodes.name AS "Pais", 
    count(recipients) AS "Cantidad" 
FROM 
    project, 
    countrycodes 
WHERE project.recipients = countrycodes.id 
GROUP BY recipients 
ORDER BY 2 ASC LIMIT 5;

/*SEXTA CONSULTA*/
WITH costo_max AS (
    SELECT total_commitments
    FROM project
    ORDER BY total_commitments DESC LIMIT 1
) SELECT 
    project_id AS "Codigo de proyecto",
    project_title AS "Nombre de proyecto",
    project.total_commitments AS "Costo total"
FROM
    project, 
    costo_max
WHERE
    project.total_commitments = costo_max.total_commitments;

/*SÉPTIMA CONSULTA*/
WITH costo_min AS (
    SELECT total_commitments
    FROM project
    ORDER BY total_commitments ASC LIMIT 1
) SELECT 
    project_id AS "Codigo de proyecto",
    project_title AS "Nombre de proyecto",
    project.total_commitments AS "Costo total"
FROM
    project, 
    costo_min
WHERE
    project.total_commitments = costo_min.total_commitments;

/*OCTAVA CONSULTA*/
SELECT 
    project_id AS "Codigo de proyecto",
    project_title AS "Nombre de proyecto",
    total_commitments AS "Costo total"
FROM project
ORDER BY total_commitments DESC LIMIT 5;

/*NOVENA CONSULTA*/
SELECT 
    project_id AS "Codigo de proyecto",
    project_title AS "Nombre de proyecto",
    total_commitments AS "Costo total"
FROM project
ORDER BY total_commitments ASC LIMIT 5;

/*DÉCIMA CONSULTA*/
SELECT
    project.project_id AS "Codigo de proyecto",
    project.project_title AS "Nombre de proyecto",
    transactions_id AS "ID de transaccion",
    transaction_isodate AS "Fecha de transaccion",
    transaction_year AS "Año de transaccion",
    transaction_value_code AS "Tipo de transaccion",
    currency.name AS "Moneda de transaccion",
    transaction_value AS "Valor de transaccion"
FROM
    transaction,
    currency,
    project
WHERE
    transaction.project_id = project.id
    AND project.project_title like "%RI-East Africa Public Health Laboratory Networking Project%"
    AND currency.id = transaction.transaction_currency
ORDER BY
    transaction.transaction_value DESC LIMIT 3;

/*
    QUERY PROVISIONAL PARA COMPROBACIÓN DE TOTALES DE TRANSACCIONES
WITH total_credito AS (
    SELECT
        project_id ,
        sum(transaction_value) AS total
    FROM
        transaction
    WHERE 
        transaction_value_code = 'C'
    GROUP BY
        project_id
), total_debito AS (
    SELECT DISTINCT
        project_id,
        sum(transaction_value) AS total
    FROM 
        transaction
    WHERE 
        transaction_value_code = 'D'
    GROUP BY
        project_id
) SELECT
    total_credito.project_id AS id_proyecto,
    project.project_id,
    project.project_title,
    (total_credito.total-total_debito.total) AS total_transaction,
    (project.total_commitments-project.total_disbursements) AS total_project
FROM 
    total_credito, project, total_debito
WHERE
    total_credito.project_id = total_debito.project_id
    AND project.id = total_credito.project_id
ORDER BY
    total_transaction DESC LIMIT 5;*/