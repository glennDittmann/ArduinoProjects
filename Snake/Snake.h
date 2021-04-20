#define PIN 6
#define NUM_PIXELS 450
#define PIXEL_WIDTH 30  
#define PIXEL_LENGTH 15

#define TRIGGER 3
#define BUTTONS 4
#define ANALOG_X 0
#define ANALOG_y 1

#define NO_INPUTS 4
#define UP 1
#define DOWN 0
#define RIGHT 3
#define LEFT 2

#define START_X 10
#define START_Y 7
#define START_LEN 4 //length of tail, without head
#define MAX_TAIL_LENGTH 100

class Snake {
    public: int head_x, head_y;
    int len;                            //length of tail, without head
    public: int tail [MAX_TAIL_LENGTH];         //TODO: add max_length which is given in constructor and is used instead of hard coded 16
    int removedTailSegment;
    int dir;
    int head_color[3] = {0, 60, 255};
    int tail_color[3] = {150, 20, 255};

    int left, right, up, down;
    int directions[5];

public:
    Snake(int x, int y, int start_len){
        this->head_x = x;
        this->head_y = y;
        this->len = start_len;
        this->tail[0] = coordsToPixelNum(this->head_x-1, this->head_y);
        for (int i=1; i<this->len; i++){
            this->tail[i] = this->coordsToPixelNum(this->head_x-(i+1), this->head_y);
        }
        this->directions[4] = 0;
        this->dir = 3;
    };

    void advance() {
        //store the pixel number, where to turn of the color
        this->removedTailSegment = this->tail[len-1];
        //iterate over the snake from back to front, so:
        //i:     0  1  2  3   4-15 | len is 4
        //  [32][33,34,35,36, NUll] becomes
        //  [32][33,33,34,35, NULL]
        for (int i = this->len-1; i > 0; i--){
            this->tail[i] = this->tail[i-1];
        }
        // set first tail segment to head coordinates:
        // [32][32,33,34,35, NULL]
        this->tail[0] = this->headPixelNum();

        //check inputs and then update head coordinates
        this->checkInputs();
        switch (this->dir) {
            case UP:
                this->head_y -= 1;
                break;
            case DOWN:
                this->head_y += 1;
                break;
            case RIGHT:
                this->head_x += 1;
                break;
            case LEFT:
                this->head_x -= 1;
                break;
        }
    }

    void eatFruit(){
        this->len++; 
    }

    bool isDead() {
        //check if head left the screen
        if (this->head_x < 0 || this->head_x > PIXEL_WIDTH-1 || this->head_y < 0 || this->head_y > PIXEL_LENGTH-1) {
            return true;
        }
        //check if snake hit itself
        for (int i = 0; i < this->len; i++){
            if (tail[i] == this->headPixelNum()) return true;
        }
        return false;
    }

    void removePixel(Adafruit_NeoPixel * strip){                                       //give a pointer to our strip object
        strip->setPixelColor(this->headPixelNum(), 0, 0, 0);
        for (int i = 0; i < len; i++) {
            strip->setPixelColor(tail[i], 0, 0, 0);
        }
    }

    void resetPosition(){
        this->head_x = START_X;
        this->head_y = START_Y;
        this->len = START_LEN;
        this->tail[0] = this->coordsToPixelNum(this->head_x-1, this->head_y);
        for (int i=1; i<this->len; i++){
            this->tail[i] = this->coordsToPixelNum(this->head_x-(i+1), this->head_y);
        }
        this->dir = RIGHT;
    }

    void setPixel(Adafruit_NeoPixel * strip) {
        strip->setPixelColor(this->headPixelNum(), 20, 60, 0);
        for (int i = 0; i < this->len; i++) {
            strip->setPixelColor(this->tail[i], 150, 20*i, 100);
        }
        strip->setPixelColor(this->removedTailSegment, 0, 0, 0);
    }

    void checkInputs(){
        this->zeroDirections();
        if(analogRead(0) < 350) left = map(analogRead(0), 400, 0, 2, 10);
        if(analogRead(0) > 750) right = map(analogRead(0), 700, 1023, 2, 10);
        if(analogRead(1) < 350) down = map(analogRead(1), 400, 0, 2, 10);
        if(analogRead(1) > 750) up = map(analogRead(1), 700, 1023, 2, 10);
        
        directions[0] = left;
        directions[1] = right;
        directions[2] = down;
        directions[3] = up;
        
        int dir_max = 0;
        int dir_max_index = 4;
        for(byte i = 0; i < 4; i++){
          if(directions[i] > dir_max){ 
            dir_max = directions[i];
            dir_max_index = i;  
          }
        }

        if((dir_max_index == UP) && (this->dir == LEFT || this->dir == RIGHT))
            this->dir = UP;
        if((dir_max_index == DOWN) && (this->dir == LEFT || this->dir == RIGHT))
            this->dir = DOWN;
        if((dir_max_index == RIGHT) && (this->dir == UP || this->dir == DOWN))
            this->dir = RIGHT;
        if((dir_max_index == LEFT) && (this->dir == UP || this->dir == DOWN))
            this->dir = LEFT;  
    }

    int coordsToPixelNum(int x, int y) {
        int pixelNumber;
        if (y % 2 == 0) {
            pixelNumber = (y+1) * 30 - x - 1;
        } else {
            pixelNumber = y * 30 + x;
        }
        return pixelNumber;
    }

    int headPixelNum() {
        return this->coordsToPixelNum(this->head_x, this->head_y);
    }

    void zeroDirections(){
      this->left = 0;
      this->right = 0;
      this->down = 0;
      this->up = 0;
    }
};
