#include <stdio.h>
#include <stdlib.h>



int get_manhattan_distance(int x1, int y1, int x2, int y2)
{
	int distance;
	
	if(x1>=x2){
		if(y1>=y2){
			distance=(x1-x2)+(y1-y2);	
		}
		if(y1<y2){
			distance=(x1-x2)+(y2-y1);
		}
	}
	if(x1<x2){
		if(y1>=y2){
			distance=(x2-x1)+(y1-y2);
		}
		if(y1<y2){
			distance=(x2-x1)+(y2-y1);
		}
	}
	return distance;
}

int main(){
	
	int lot_size, num_of_cars, x, y, best_spot_x, best_spot_y;
	
  // get parking lot size
	printf("Size: ");
	scanf("%d", &lot_size);
	
	
	
  if((lot_size<1)||(lot_size>50)){
		printf("Size must be between 50 and 1");
		printf("Size: ");
		scanf("%d", &lot_size);
	}

  // get number of cars
  printf("Cars: ");
	scanf("%d", &num_of_cars);
	
  if(num_of_cars == 0){
		printf("Best Slot Found In: 1 1\n");
		return 0;
	}	

  	if(num_of_cars>=lot_size*lot_size){
		printf("Best Slot Found In: 0 0\n");
		return 0;
	}


  // Initialize the Parking Lot
  int parking_lot[lot_size][lot_size];
  for (int i = 0; i < lot_size; i++)
  { 
    for (int k = 0; k < lot_size; k++)
    { 
      parking_lot[i][k] = 0; 
    }
  }

  // Read and update Car Locations
	int car_locations[num_of_cars*2];
	for(int i = 0 ; i < num_of_cars; i++){
		printf("Locations: ");
		scanf("%d%d", &x, &y);
		
		if((x<=lot_size)&&(y<=lot_size)){
		
		
		car_locations[2*i]=x-1;
		car_locations[2*i+1]=y-1;

    //Update the Parking Lot for the filled spot
		
		parking_lot[x - 1][y - 1] = 1;
		}
		
	}

  
 
  int max_manhattan_distance = 0; 
  // Look for an available spot
  // Starting from the end of parking lot because being near to entrance is favorable 
  for (int i = lot_size - 1; i >= 0; i--)
  {
    for (int j = lot_size - 1; j >= 0; j--)
    {
      // For each empty parking spot, calculate Manhattan distances to filled spots
      if(parking_lot[i][j] == 0)
      { 
        int distance_to_nearest_car = lot_size;
        for (int k = 0; k <num_of_cars; k++)
        { 
          int car_location_x = car_locations[2*k];
          int car_location_y = car_locations[2*k+1];
          
          if((car_location_x>lot_size)||(car_location_y>lot_size)){
          	break;}
        
        
          	int distance_to_current_car = get_manhattan_distance(i, j, car_location_x, car_location_y);

          	if (distance_to_current_car < distance_to_nearest_car){
          		
            	distance_to_nearest_car = distance_to_current_car;
          		}
     		
        }
        
        
        // If we found a spot that has a higher distance to the nearest car, we override the best_spot. Since we started from the end of the parking lot, the spot nearest to the entrance will override the best_spot if the distances are equal.
        if(max_manhattan_distance <= distance_to_nearest_car )
        {
          max_manhattan_distance = distance_to_nearest_car; 
          best_spot_x = i + 1;
          best_spot_y = j + 1;
        } 
    

      }
    }
  }
	
	printf("Best Slot Found In: %d %d\n", best_spot_x, best_spot_y);

	return 0;
}
