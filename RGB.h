// /*
// --------------------------------------------------------------->> RGB RING LIGHT CONTROL <<---------------------------------------------------------------
// */


//     //  bot_led("red");
//     //  delay(1000);
//     // bot_led("rose");
//     //      delay(1000);
//     //   bot_led("magenta");
//     //   delay(1000);
//     //   bot_led("violet");
//     //   delay(1000);
//     //   bot_led("blue");
//     //   delay(1000);
//     //  bot_led("azure");
//     //  delay(1000);
//     //  bot_led("cyan");
//     //  delay(1000);
//     //  bot_led("spring_green");
//     //  delay(1000);
//     //   bot_led("green");
//     //   delay(1000);
//     //   bot_led("chartreuse");
//     //   delay(1000);
//     //   bot_led("yellow");
//     //   delay(1000);
//     //  bot_led("orange");


// void top_led(char* color){
// if      (color == "red")          {analogWrite(Gre_top,0);  analogWrite(Blu_top,0);  for(int red = 0;red <= 255;red++)        {analogWrite(Red_top,red);}}
// else if (color == "rose")         {analogWrite(Gre_top,0);  analogWrite(Red_top,255);for(int blu = 0;blu <= 128;blu++)        {analogWrite(Blu_top,blu);}}
// else if (color == "magenta")      {analogWrite(Gre_top,0);  analogWrite(Red_top,255);for(int blu = 128;blu <= 255;blu++)      {analogWrite(Blu_top,blu);}}
// else if (color == "violet")       {analogWrite(Gre_top,0);  analogWrite(Blu_top,255);for(int red = 255;red >= 128;red--)      {analogWrite(Red_top,red);}}
// else if (color == "blue")         {analogWrite(Gre_top,0);  analogWrite(Blu_top,255);for(int red = 255;red >= 0;red--)        {analogWrite(Red_top,red);}}
// else if (color == "azure")        {analogWrite(Blu_top,255);analogWrite(Red_top,0);  for(int gre = 0;gre <= 128;gre++)        {analogWrite(Gre_top,gre);}}
// else if (color == "cyan")         {analogWrite(Blu_top,255);analogWrite(Red_top,0);  for(int gre = 128;gre <= 255;gre++)      {analogWrite(Gre_top,gre);}}
// else if (color == "spring_green") {analogWrite(Gre_top,255);analogWrite(Red_top,0);  for(int blu = 255;blu >= 128;blu--)      {analogWrite(Blu_top,blu);}}
// else if (color == "green")        {analogWrite(Gre_top,255);analogWrite(Red_top,0);  for(int blu = 128;blu >= 0;blu--)        {analogWrite(Blu_top,blu);}}
// else if (color == "chartreuse")   {analogWrite(Gre_top,255);analogWrite(Blu_top,0);  for(int red = 0;red <= 128;red++)        {analogWrite(Red_top,red);}}
// else if (color == "yellow")       {analogWrite(Gre_top,255);analogWrite(Blu_top,0);  for(int red = 128;red <= 255;red++)      {analogWrite(Red_top,red);}}
// else if (color == "orange")       {analogWrite(Gre_top,255);analogWrite(Blu_top,0);  for(int red = 255;red >= 128;red--)      {analogWrite(Red_top,red);}}
// }
// void bot_led(char* color){
// if      (color == "red")          {analogWrite(Gre_bot,0);  analogWrite(Blu_bot,0);  for(int red = 0;red <= 255;red++)        {analogWrite(Red_bot,red);}}
// else if (color == "rose")         {analogWrite(Gre_bot,0);  analogWrite(Red_bot,255);for(int blu = 0;blu <= 128;blu++)        {analogWrite(Blu_bot,blu);}}
// else if (color == "magenta")      {analogWrite(Gre_bot,0);  analogWrite(Red_bot,255);for(int blu = 128;blu <= 255;blu++)      {analogWrite(Blu_bot,blu);}}
// else if (color == "violet")       {analogWrite(Gre_bot,0);  analogWrite(Blu_bot,255);for(int red = 255;red >= 128;red--)      {analogWrite(Red_bot,red);}}
// else if (color == "blue")         {analogWrite(Gre_bot,0);  analogWrite(Blu_bot,255);for(int red = 255;red >= 0;red--)        {analogWrite(Red_bot,red);}}
// else if (color == "azure")        {analogWrite(Blu_bot,255);analogWrite(Red_bot,0);  for(int gre = 0;gre <= 128;gre++)        {analogWrite(Gre_bot,gre);}}
// else if (color == "cyan")         {analogWrite(Blu_bot,255);analogWrite(Red_bot,0);  for(int gre = 128;gre <= 255;gre++)      {analogWrite(Gre_bot,gre);}}
// else if (color == "spring_green") {analogWrite(Gre_bot,255);analogWrite(Red_bot,0);  for(int blu = 255;blu >= 128;blu--)      {analogWrite(Blu_bot,blu);}}
// else if (color == "green")        {analogWrite(Gre_bot,255);analogWrite(Red_bot,0);  for(int blu = 128;blu >= 0;blu--)        {analogWrite(Blu_bot,blu);}}
// else if (color == "chartreuse")   {analogWrite(Gre_bot,255);analogWrite(Blu_bot,0);  for(int red = 0;red <= 128;red++)        {analogWrite(Red_bot,red);}}
// else if (color == "yellow")       {analogWrite(Gre_bot,255);analogWrite(Blu_bot,0);  for(int red = 128;red <= 255;red++)      {analogWrite(Red_bot,red);}}
// else if (color == "orange")       {analogWrite(Gre_bot,255);analogWrite(Blu_bot,0);  for(int red = 255;red >= 128;red--)      {analogWrite(Red_bot,red);}}
// }
// // void left_led(char* color){
// // if      (color == "red")          {analogWrite(Gre_left,0);  analogWrite(Blu_left,0);  for(int red = 0;red <= 255;red++)      {analogWrite(Red_left,red);}}
// // else if (color == "rose")         {analogWrite(Gre_left,0);  analogWrite(Red_left,255);for(int blu = 0;blu <= 128;blu++)      {analogWrite(Blu_left,blu);}}
// // else if (color == "magenta")      {analogWrite(Gre_left,0);  analogWrite(Red_left,255);for(int blu = 128;blu <= 255;blu++)    {analogWrite(Blu_left,blu);}}
// // else if (color == "violet")       {analogWrite(Gre_left,0);  analogWrite(Blu_left,255);for(int red = 255;red >= 128;red--)    {analogWrite(Red_left,red);}}
// // else if (color == "blue")         {analogWrite(Gre_left,0);  analogWrite(Blu_left,255);for(int red = 255;red >= 0;red--)      {analogWrite(Red_left,red);}}
// // else if (color == "azure")        {analogWrite(Blu_left,255);analogWrite(Red_left,0);  for(int gre = 0;gre <= 128;gre++)      {analogWrite(Gre_left,gre);}}
// // else if (color == "cyan")         {analogWrite(Blu_left,255);analogWrite(Red_left,0);  for(int gre = 128;gre <= 255;gre++)    {analogWrite(Gre_left,gre);}}
// // else if (color == "spring_green") {analogWrite(Gre_left,255);analogWrite(Red_left,0);  for(int blu = 255;blu >= 128;blu--)    {analogWrite(Blu_left,blu);}}
// // else if (color == "green")        {analogWrite(Gre_left,255);analogWrite(Red_left,0);  for(int blu = 128;blu >= 0;blu--)      {analogWrite(Blu_left,blu);}}
// // else if (color == "chartreuse")   {analogWrite(Gre_left,255);analogWrite(Blu_left,0);  for(int red = 0;red <= 128;red++)      {analogWrite(Red_left,red);}}
// // else if (color == "yellow")       {analogWrite(Gre_left,255);analogWrite(Blu_left,0);  for(int red = 128;red <= 255;red++)    {analogWrite(Red_left,red);}}
// // else if (color == "orange")       {analogWrite(Gre_left,255);analogWrite(Blu_left,0);  for(int red = 255;red >= 128;red--)    {analogWrite(Red_left,red);}}
// // }
// // void right_led(char* color){
// // if      (color == "red")          {analogWrite(Gre_right,0);  analogWrite(Blu_right,0);  for(int red = 0;red <= 255;red++)    {analogWrite(Red_right,red);}}
// // else if (color == "rose")         {analogWrite(Gre_right,0);  analogWrite(Red_right,255);for(int blu = 0;blu <= 128;blu++)    {analogWrite(Blu_right,blu);}}
// // else if (color == "magenta")      {analogWrite(Gre_right,0);  analogWrite(Red_right,255);for(int blu = 128;blu <= 255;blu++)  {analogWrite(Blu_right,blu);}}
// // else if (color == "violet")       {analogWrite(Gre_right,0);  analogWrite(Blu_right,255);for(int red = 255;red >= 128;red--)  {analogWrite(Red_right,red);}}
// // else if (color == "blue")         {analogWrite(Gre_right,0);  analogWrite(Blu_right,255);for(int red = 255;red >= 0;red--)    {analogWrite(Red_right,red);}}
// // else if (color == "azure")        {analogWrite(Blu_right,255);analogWrite(Red_right,0);  for(int gre = 0;gre <= 128;gre++)    {analogWrite(Gre_right,gre);}}
// // else if (color == "cyan")         {analogWrite(Blu_right,255);analogWrite(Red_right,0);  for(int gre = 128;gre <= 255;gre++)  {analogWrite(Gre_right,gre);}}
// // else if (color == "spring_green") {analogWrite(Gre_right,255);analogWrite(Red_right,0);  for(int blu = 255;blu >= 128;blu--)  {analogWrite(Blu_right,blu);}}
// // else if (color == "green")        {analogWrite(Gre_right,255);analogWrite(Red_right,0);  for(int blu = 128;blu >= 0;blu--)    {analogWrite(Blu_right,blu);}}
// // else if (color == "chartreuse")   {analogWrite(Gre_right,255);analogWrite(Blu_right,0);  for(int red = 0;red <= 128;red++)    {analogWrite(Red_right,red);}}
// // else if (color == "yellow")       {analogWrite(Gre_right,255);analogWrite(Blu_right,0);  for(int red = 128;red <= 255;red++)  {analogWrite(Red_right,red);}}
// // else if (color == "orange")       {analogWrite(Gre_right,255);analogWrite(Blu_right,0);  for(int red = 255;red >= 128;red--)  {analogWrite(Red_right,red);}}
// // }