#include <Form.hpp>
#include <Canvas.hpp>
#include <TcpIpServer.hpp>
#include <mutex>

class DrawingServer final : public Form {
private:

    Canvas canvas_;
    error_code server_error_;
    TcpIpServer server_;
    std::mutex coord_mtx_;
    int x_;
    int y_;

public:

    explicit DrawingServer(const HINSTANCE hInstance)noexcept(true) :
        Form::Form(hInstance),
        canvas_{ hInstance, 900, 1000, Color{ 255, 255, 255 } },
        server_{ 23672, server_error_ },
        coord_mtx_{},
        x_{ 0 },
        y_{ 0 }{
        
    }

    bool Run()noexcept(true) {

        if (server_error_ != error_code::Success)
            return false;

        server_.InitProcessConnectionCreating([](ConnectionInterface connection)noexcept->void {
            
            MessageBoxA(NULL, u8"New connection!", u8"Message!", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
            
            });

        server_.InitProcessConnectionFunction([this](ConnectionInterface connection)noexcept->void {
            
            std::lock_guard<std::mutex> guard{ coord_mtx_ };

            if (x_ != 0 && y_ != 0) {

                Packet coordinats{ sizeof(int) * 2 };
                int* ints = reinterpret_cast<int*>(coordinats.Data());

                ints[0] = x_;
                ints[1] = y_;

                connection.SendPacket(&coordinats);
                
                x_ = 0;
                y_ = 0;

            }
            
            });

        server_error_ = server_.Start();

        if (server_error_ != error_code::Success)
            return false;

        canvas_.InitCanvasProc([this](Message& message)noexcept->bool {

             switch (message.key_type.action_) {
                case Action::MouseMove:

                    coord_mtx_.lock();

                    x_ = message.X();
                    y_ = message.Y();

                    coord_mtx_.unlock();
                    
                    canvas_.SetPixel(x_, y_, Color{ 0, 0, 0 });

                    return true;

            default:

                return false;

            };
            
            });

        Form::Create(L"NetworkClient");
        canvas_.Create(Form::Handle());

        Form::Show(SW_MAXIMIZE);
        canvas_.Show(SW_SHOW);

        Form::Size(960, 1080);
        Form::Run();

        return true;

    }

    void Stop()noexcept(true) {

        if(server_.IsRunning())
            server_.Stop();

    }

    ~DrawingServer()noexcept(true){


    }

};

int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow) {

    DrawingServer server{ hInstance };
    
    if (server.Run()) {
        
        server.Stop();
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}