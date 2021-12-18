echo "~Limpiando tablas..."
mysql -u admin -p < drop_tables.sql
echo "~Creando tablas temporales..."
mysql -u admin -p < temporales.sql
echo "~Creando tablas del modelo ER..."
mysql -u admin -p < tablas.sql
mysql --local-infile=1 -u admin -p < transactions_control.sql
echo "~Datos de transactions.csv cargados"
mysql --local-infile=1 -u admin -p < geonames_control.sql
echo "~Datos de geonames.csv cargados"
mysql --local-infile=1 -u admin -p < level_control.sql
echo "~Datos de level_1a.csv cargados"
mysql --local-infile=1 -u admin -p < projects_control.sql
echo "~Datos de projects.csv cargados"
mysql --local-infile=1 -u admin -p < locations_control.sql
echo "~Datos de locations.csv cargados"
mysql --local-infile=1 -u admin -p < country_codes_control.sql
echo "~Datos de country_codes.tsv cargados"