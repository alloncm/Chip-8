#include<cstdio>
#include<cstring>
#include<vector>
#include<exception>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include"Chip8Cpu.h"
#include"Chip8Machine.h"
#include"Opcodes.h"

static constexpr unsigned int INPUT_FRAME_TIME_UPDATE = 3;
static constexpr unsigned int OPCODES_PER_FRAME = 10;
static constexpr unsigned int PIXEL_SIZE = 10;  // a larger number make the framebuffer too large and causes a stack overflow
static constexpr unsigned int SCREEN_WIDTH = Chip8Cpu::SCREEN_WIDTH * PIXEL_SIZE;
static constexpr unsigned int SCREEN_HEIGHT = Chip8Cpu::SCREEN_HIGHT * PIXEL_SIZE;
static constexpr uint32_t PIXEL_COLOR = 0x0000FF; // blue
static constexpr uint32_t BACKGROUND_COLOR = 0xFFFFFF; // white

void UpdateInput(std::array<bool, Chip8Cpu::NUMBER_OF_KEYS>& input)
{
    const uint8_t* state = SDL_GetKeyboardState(nullptr);
    input[0] = state[SDL_SCANCODE_1];
    input[1] = state[SDL_SCANCODE_2];
    input[2] = state[SDL_SCANCODE_3];
    input[3] = state[SDL_SCANCODE_4];
    input[4] = state[SDL_SCANCODE_Q];
    input[5] = state[SDL_SCANCODE_W];
    input[6] = state[SDL_SCANCODE_E];
    input[7] = state[SDL_SCANCODE_R];
    input[8] = state[SDL_SCANCODE_A];
    input[9] = state[SDL_SCANCODE_S];
    input[10] = state[SDL_SCANCODE_D];
    input[11] = state[SDL_SCANCODE_F];
    input[12] = state[SDL_SCANCODE_Z];
    input[13] = state[SDL_SCANCODE_X];
    input[14] = state[SDL_SCANCODE_C];
    input[15] = state[SDL_SCANCODE_V];
}

int main(int argc, char **argv){
    if (argc < 2){
        printf("error not enough params for the pgrogram\n");
        return EXIT_FAILURE;
    }
    std::string programName(argv[1]);

    uint16_t fontsSpritesAdresses[] = { 0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75 };
    Chip8Cpu chip8Cpu(fontsSpritesAdresses);
    OpcodeRunner opcodeRunner = OpcodeRunner(chip8Cpu);

    Chip8Machine vm(chip8Cpu, opcodeRunner);
    vm.LoadProgram(programName);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Event event;
    while (true){
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }

        std::array<bool, Chip8Cpu::NUMBER_OF_KEYS> input;
        UpdateInput(input);
        vm.SetInput(input);

        try
        {
	        for (int i = 0; i < OPCODES_PER_FRAME; i++)
	        {
	        	vm.ChipCycle();
	        }

	        vm.TimersCycle();
        }
        catch(const char* msg)
        {
            printf("%s\n", msg);
            return EXIT_FAILURE;
        }

        std::array<bool, Chip8Cpu::SCREEN_HIGHT * Chip8Cpu::SCREEN_WIDTH> buffer = vm.GetScreenBuffer();
        uint32_t sdl_buffer[SCREEN_HEIGHT * SCREEN_WIDTH] = {0};
        for (int i = 0; i < Chip8Cpu::SCREEN_HIGHT; i++)
	    {
		    for (int j = 0; j < Chip8Cpu::SCREEN_WIDTH; j++)
		    {
		    	int y = i * PIXEL_SIZE;
		    	int x = j * PIXEL_SIZE;
		    	for (unsigned int tempX = x; tempX < x + PIXEL_SIZE; tempX++)
		    	{
		    		for (unsigned int tempY = y; tempY < y + PIXEL_SIZE; tempY++)
		    		{
		    			sdl_buffer[(tempY * SCREEN_WIDTH) + tempX] = buffer[i * Chip8Cpu::SCREEN_WIDTH + j] ? PIXEL_COLOR : BACKGROUND_COLOR;
		    		}
		    	}
		    }
	    }

        void *pixels = nullptr;
        int row_length = 0;
        SDL_LockTexture(texture, nullptr, &pixels, &row_length);
        std::memcpy(pixels, sdl_buffer, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}