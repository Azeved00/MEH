
namespace State
{

    typedef enum State {
        GamePlay,
        Pause,
        TitleScreen,
        Settings,
        GeneratingWorld,
        LoadingWorld,
        ExitGame,
        Battle,
        Pokedex,
        Save
    } State;


    namespace TitleScreen
    {
        void Update();
        void Draw();
        void HandleInput();
    }
}
