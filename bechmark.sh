#!/usr/bin/env bash

# Configuración de rangos
GAMES=100
TURNS_LIST=(1000 10000 100000 1000000 10000000)
THREADS_LIST=($(seq 1 24))
OUTPUT_FILE="benchmark_results.csv"

# Encabezado del archivo de salida
echo "games,turns,threads,real_seconds,user_seconds,sys_seconds" > "$OUTPUT_FILE"

# Comprobación de existencia del binario
if [ ! -x "./monopoly" ]; then
    echo "Error: ./monopoly no existe o no tiene permisos de ejecución."
    exit 1
fi

echo "Iniciando benchmark..."

for turns in "${TURNS_LIST[@]}"; do
    for threads in "${THREADS_LIST[@]}"; do
        echo -n "Ejecutando: turns=$turns, threads=$threads... "
        
        # Ejecución capturando el tiempo formateado (en segundos)
        # %e: real elapsed time, %U: user CPU time, %S: system CPU time
        time_output=$(/usr/bin/time -f "%e,%U,%S" ./monopoly --turns "$turns" --games "$GAMES" --threads "$threads" --parallel 2>&1 >/dev/null)
        
        # Guardar en CSV
        echo "$GAMES,$turns,$threads,$time_output" >> "$OUTPUT_FILE"
        echo "Listo: ${time_output}s"
    done
done

echo "Benchmark finalizado. Resultados guardados en $OUTPUT_FILE."