void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'H';
    *(video_memory + 1) = 0x07;
    *(video_memory + 2) = 'e';
    *(video_memory + 3) = 0x07;
    *(video_memory + 4) = 'l';
    *(video_memory + 5) = 0x07;
    *(video_memory + 6) = 'l';
    *(video_memory + 7) = 0x07;
    *(video_memory + 8) = 'o';
    *(video_memory + 9) = 0x07;
    *(video_memory + 10) = ' ';
    *(video_memory + 11) = 0x07;
    *(video_memory + 12) = 'w';
    *(video_memory + 13) = 0x07;
    *(video_memory + 14) = 'o';
    *(video_memory + 15) = 0x07;
    *(video_memory + 16) = 'r';
    *(video_memory + 17) = 0x07;
    *(video_memory + 18) = 'l';
    *(video_memory + 19) = 0x07;
    *(video_memory + 20) = 'd';
    *(video_memory + 21) = 0x07;
}
