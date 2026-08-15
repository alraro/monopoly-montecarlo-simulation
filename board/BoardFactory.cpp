#include "BoardFactory.hpp"
#include "BoardBuilder.hpp"

namespace BoardFactory {

    Board createDefaultBoard() {
        BoardBuilder builder;
        return builder.addStartSquare()
            .addPropertySquare("Ronda de Valencia")
            .addCommunitySquare()
            .addPropertySquare("Plaza de Lavapies")
            .addPropertySquare("Impuestos (Tipo a implementar todavia)")
            .addPropertySquare("Estacion de Goya (Tipo a implementar todavia)")
            .addPropertySquare("GLORIETA CUATRO CAMINOS")
            .addLuckSquare()
            .addPropertySquare("AVENIDA DE REINA VICTORIA")
            .addPropertySquare("CALLE DE BRAVO MURILLO")
            .addJailSquare()
            .addPropertySquare("GLORIETA DE BILBAO")
            .addPropertySquare("COMPAÑÍA DISTRIBUCIÓN DE ELECTRICIDAD")
            .addPropertySquare("CALLE DE ALBERTO AGUILERA")
            .addPropertySquare("CALLE DE FUENCARRAL")
            .addPropertySquare("ESTACIÓN DE LAS DELICIAS")
            .addPropertySquare("AVENIDA DE FELIPE II")
            .addCommunitySquare()
            .addPropertySquare("CALLE DE VELÁZQUEZ")
            .addPropertySquare("CALLE DE SERRANO")
            .addParkingSquare()
            .addPropertySquare("AVENIDA DE AMÉRICA")
            .addLuckSquare()
            .addPropertySquare("CLL. DE MARÍA DE MOLINA")
            .addPropertySquare("CALLE DE CEA BERMÚDEZ")
            .addPropertySquare("ESTACIÓN DEL MEDIODÍA")
            .addPropertySquare("AVENIDA DE LOS REYES CATÓLICOS")
            .addPropertySquare("CALLE DE BAILÉN")
            .addPropertySquare("COMPAÑÍA DISTRIBUCIÓN DE AGUAS")
            .addPropertySquare("PLAZA DE ESPAÑA")
            .addGoToJailSquare()
            .addPropertySquare("PUERTA DEL SOL")
            .addPropertySquare("CALLE DE ALCALÁ")
            .addCommunitySquare()
            .addPropertySquare("GRAN VÍA")
            .addPropertySquare("ESTACIÓN DEL NORTE")
            .addLuckSquare()
            .addPropertySquare("PASEO DE LA CASTELLANA")
            .addPropertySquare("TASA DE LUJO")
            .addPropertySquare("PASEO DEL PRADO")
            .build();
    }
}