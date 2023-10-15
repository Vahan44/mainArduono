bool tag1;
bool tag2;
int pult_data;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (pult_data == 12) {
    tag1 = 1;
    tag2 = 0;
  }
  if (pult_data == 22) {
    tag1 = 0;
    tag2 = 1;
  }

  if (tag1 == 1) {
    //rejim1
  }
  if (tag2 == 1) {
    //rejim2
  }


}
