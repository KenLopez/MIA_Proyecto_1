#Admin_21
echo "~Limpiando tablas..."
mysql -u admin -p < drop_tables.sql
echo "~Creando tablas temporales..."
mysql -u admin -p < temporales.sql
echo "~Creando tablas del modelo ER..."
mysql -u admin -p < tablas.sql
echo "~Cargando datos de transactions.csv..."
mysql --local-infile=1 -u admin -p < transactions_control.sql
echo "~Cargando datos de geonames.csv..."
mysql --local-infile=1 -u admin -p < geonames_control.sql
echo "~Cargando datos de level_1a.csv..."
mysql --local-infile=1 -u admin -p < level_control.sql
echo "~Cargando datos de projects.csv..."
mysql --local-infile=1 -u admin -p < projects_control.sql
echo "~Cargando datos de locations.csv..."
mysql --local-infile=1 -u admin -p < locations_control.sql
echo "~Cargando datos de country_codes.tsv..."
mysql --local-infile=1 -u admin -p < country_codes_control.sql
echo "~Cargando datos de temporales..."
mysql -u admin -p < insert.sql