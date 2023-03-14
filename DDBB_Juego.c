//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    MYSQL *conn; 
    MYSQL_RES *res; 
    MYSQL_ROW row;  
    int duracion_min = 9;  // Duración mínima de las partidas en minutos
    char query[500]; 
    
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
    // Conectar a la base de datos JUEGO
	conn = mysql_real_connect (conn, "localhost","user", "pass", "JUEGO",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
    }
    
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	err=mysql_query (conn, "SELECT * FROM JUEGO");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
    // Consulta SQL para obtener los ganadores de las partidas que han durado más de 10 minutos
    sprintf(query, "SELECT PARTIDAS.GANADOR FROM (JUGADORES, PARTIDAS, PARTICIPACION) WHERE  PARTIDAS.DURACION > 9 AND    JUGADORES.ID = PARTICIPACION.ID_J AND    PARTIDAS.ID  = PARTICIPACION.ID_P; > %d", duracion_min);
    
    // Ejecutar la consulta SQL
    if (mysql_query(conn, query)) {
        printf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    // Resultado
    res = mysql_store_result(conn);
    
    // Mostrar los resultados
    printf("Ganadores de las partidas que han durado más de %d minutos:\n", duracion_min);
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Partida ID: %s, Ganador: %s\n", row[0], row[1]);
    }
    
    // Liberar los recursos y cerrar la conexión
    mysql_close(conn);
    
    exit (0);
}
