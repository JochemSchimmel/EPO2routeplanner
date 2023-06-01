struct Coords{
    int x;
    int y;
};



struct Coords * stationToCoords(int stations, int stationCoords, int numberOfDestinations){
    int i = 0;
    struct Coords * destinationCoordList[numberOfDestinations];

    for (i = 0; i < numberOfDestinations; i++){
        destinationCoordList[i].x = stationCoords[numberOfDestinations[i]][0];
        destinationCoordList[i].y = stationCoords[numberOfDestinations[i]][1];
    }
    return &destinationCoordList[0];
}

int main{


    return 0;
}