#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	char* CLAVE;
	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	CLAVE = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, CLAVE);



	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);
	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	enviar_mensaje(CLAVE, conexion);
	paquete(conexion);
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("tp0.log", "Log create", true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("tp0.config");
	if (nuevo_config == NULL) {
		printf("No se pudo crear el config :( \n");
		exit(1);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
 	char* leido;

	leido = readline("> ");
	while (leido!=NULL&&leido[0]!='\0'){
		log_info(logger, leido);
		free(leido);
		leido = readline("> ");
	}
		free(leido); 

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete	
	leido = readline("> ");
	while (leido!=NULL&&leido[0]!='\0'){
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
		leido = readline("> ");
	}
		free(leido); 
		enviar_paquete(paquete, conexion);
		eliminar_paquete(paquete);

	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
