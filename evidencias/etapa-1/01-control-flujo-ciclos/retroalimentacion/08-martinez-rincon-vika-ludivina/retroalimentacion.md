# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 08 — Martinez Rincon Vika Ludivina

## Programa 1 — Encuesta de satisfacción

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (8 o más) | Calificaciones 10, 8, 7, 3 | Satisfechos 2, insatisfechos 2 | Satisfechos 2, insatisfechos 2 | ✅ |
| Reporte | Mismo caso | Total de encuestas, satisfechos e insatisfechos | Falta el total de encuestas capturadas | ❌ |

**Observaciones:**

- Validación de la cantidad y, además, del rango de la calificación (1 a 10): muy bien.
- Clasificación correcta (8 exacto cuenta como satisfecho).
- Al reporte le falta el total de encuestas capturadas, que el enunciado pedía explícitamente.

**Recomendaciones:**

- system("clear") es un comando de Linux/Mac; en Windows (Dev-C++) el equivalente es system("cls").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//VLMR_[matrícula omitida]_D4_P1_E1 | Vika Ludivina Martinez Rincon

#include <iostream>
using namespace std;

int main(){
    
    //CanEnc: Cantidad de encuesras | Cal: Calificacion | Sat: Clientes satisfechos | InSat: Clientes insatisfechos
    int CanEnc, Cal=0, Sat=0, InSat=0;
    //Pedir cantidad de encuestas
    do {
        cout<<" Cuantas enuestas se van a capturar: ";
        cin>>CanEnc;
        if (CanEnc<=0) {
            cout<<" ERROR. El numero tiene que ser mayor a 0 "<<endl;
        }
    } while (CanEnc<=0);
    //Capturar encuestas
    for (int i=1; i<=CanEnc; i++) {
        do {
            cout<<" Ingresa la calificacion que le das al restaurante (1 al 10): ";
            cin>>Cal;
        //Validar la cal.
            // [Revisión, línea 24] Bien: validación extra del rango de 1 a 10.
            if (Cal<1 || Cal>10) {
                cout<<" ERROR. La calificacion debe ser un numero del 1 al 10 y numero entero "<<endl<<endl;
            }
        } while (Cal<1 || Cal>10);
    //Clasificar cal. d los clientes
        // [Revisión, línea 29] Correcto: 8 exacto cuenta como satisfecho.
        if (Cal>=8) {
            cout<<" El cliente esta satisfecho "<<endl<<endl;
            Sat++;
        } else {
            cout<<" El cliente esta insatisfecho "<<endl<<endl;
            InSat++;
        }
    }
    // [Revisión, línea 37] system("clear") es de Linux/Mac; en Dev-C++ (Windows) es system("cls").
    system("clear");
    cout<<" **** REPORTE FINAL **** "<<endl<<endl;
    // [Revisión, línea 39] FALTA: el enunciado pide mostrar también el total de encuestas capturadas.
    cout<<" Clientes Satisfechos: "<< Sat<<endl;
    cout<<" Clientes Insatisfechos: "<<InSat<<endl<<endl<<endl<<endl;
    return 0;
}
```

## Programa 2 — Taquilla de cine

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Vuelve a pedir la opción | Vuelve a pedirla | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Ventas y reporte | General 2+1, VIP 3, 3D 1 | General 3 ($195), VIP 3 ($330), 3D 1 ($95), 7 boletos, $620 | Idéntico al esperado | ✅ |

**Observaciones:**

- Constantes, validaciones, switch y reporte correctos.
- Buen detalle documentar con comentarios qué significa cada variable abreviada.

**Recomendaciones:**

- Los acumuladores de dinero (TG, TV, T3) son int; funcionan con estos precios porque no tienen centavos, pero para montos conviene usar double.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//VLMR_[matrícula omitida]_D4_P2_E1 | Vika Ludivina Martinez Rincon

#include <iostream>
using namespace std;
int main(){
    //Precio de los boletos
    //PG: Precio General | PV: Precio VIP | P3: Precio 3D
    // [Revisión, línea 8] Bien: constantes, con un comentario que explica cada abreviatura.
    const double PG=65.00, PV=110.00, P3=95.00;
    //Contadores de boletos vendidos
    //BG: Boleto General | BV: Boleto Vip | B3: Boleto 3D
    int BG=0, BV=0, B3=0;
    //Dinero que se recaudo
    //TG: Total General | TV: Total VIP | T3: Total 3D | op: opcion | CanBol: Cantidad de boletos
    // [Revisión, línea 14] Tipo de dato: los montos deberían ser double; con int funciona solo porque estos precios no tienen centavos.
    int TG=0, TV=0, T3=0;
    int CanBol=0;
    int op;
    do {
        cout<< " >>>>>>>>>> T A Q U I L L A   D E   C I N E <<<<<<<<<<" <<endl<<endl;
        cout<<" 1. Boleto General: $65.00 " <<endl;
        cout<<" 2. Boleto V I P: $110.00 " <<endl;
        cout<<" 3. Boleto sala 3D: $95.00 " <<endl;
        cout<<" 4. == CERRAR TAQUILLA == " <<endl <<endl<<endl;
        cout<<" SELECCIONE UNA OPCIÓN: ";
        cin>>op;
        //Validar opcion
        while (op<1 || op>4) {
            cout<<" OPCION INVALIDA. Seleccione un numero del 1 al 4: ";
            cin>>op;
        }
        if (op!=4) {
            cout<<" Cuantos boletos desea comprar: ";
            cin>>CanBol;
            //Validar cantidad de boletos
            while (CanBol <= 0) {
                cout<<" CANTIDAD INVALIDA. Ingrese un numero entero y positivo: ";
                cin>>CanBol;
            }
            switch (op) {
                case 1:
                    BG=BG+CanBol;
                    TG=TG+CanBol*PG;
                    break;
                case 2:
                    BV=BV+CanBol;
                    TV=TV+CanBol*PV;
                    break;
                case 3:
                    B3=B3+CanBol;
                    T3=T3+CanBol*P3;
                    break;
            }
            cout<<" Venta registrada "<<endl;
        }
    } while (op!=4);
    cout<<" <<<<<<<<<< R E P O R T E   F I N A L >>>>>>>>>>" <<endl <<endl <<endl;
    cout<<" Total de Boletos Generales vendidos: "<<BG<<endl;
    cout<<" Monto total de Boletos Generales: $"<<TG<<endl <<endl;
    cout<<" Total de Boletos V I P vendidos: "<<BV<<endl;
    cout<<" Monto total de Boletos V I P: $"<<TV<<endl <<endl;
    cout<<" Total de boletos en Sala 3D: "<<B3<<endl;
    cout<<" Monto total de boletos en sala 3D vendidos: $"<<T3<<endl <<endl;
    cout<<" Boletos totales vendidos: "<<BG+BV+B3<<endl;
    cout<<" Monto total de boletos vendidos: $"<<TG+TV+T3<<endl <<endl <<endl;
    return 0;
}
```

## Comentario general

Muy buen trabajo. La lógica es correcta en ambos programas; solo faltó el total de encuestas en el reporte del Programa 1.
