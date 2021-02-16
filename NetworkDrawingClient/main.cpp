#include <Form.hpp>
#include <Canvas.hpp>
#include <TcpIpClient.hpp>
#include <mutex>

class DrawingClient final :public Form {

private:

    Canvas canvas_;
    TcpIpClient client_;
    error_code client_error_;
    int x_;
    int y_;

public:

    explicit DrawingClient(const HINSTANCE hInstance)noexcept(true) :
        Form::Form{ hInstance },
        canvas_{ hInstance, 900, 1000, Color{ 255, 255, 255 } },
        client_{ client_error_ },
        client_error_{ error_code::Success },
        x_{ 0 },
        y_{ 0 }{}

    bool Run()noexcept(true) {

        if (client_error_ != error_code::Success)
            return false;

        client_.InitProcessConnectionPacketsFunction([this](ConnectionInterface connection, Packet packet)noexcept->void {
            
            if (packet.Size() != sizeof(int) * 2)
                return;

            int* coordinats = reinterpret_cast<int*>(packet.Data());
           
            x_ = coordinats[0];
            y_ = coordinats[1];

            canvas_.SetPixel(x_, y_, Color{ 0, 0, 0 });

            });

        client_error_ = client_.Connect("127.0.0.1", 23672);

        if (client_error_ != error_code::Success)
            return false;

        Form::Create(L"DrawingClient");
        canvas_.Create(Form::Handle());

        Form::Show(SW_SHOW);
        canvas_.Show(SW_SHOW);

        Form::Size(960, 1080);

        client_.Start();
        Form::Run();

        return true;
    }

    void Stop()noexcept(true) {

        client_.Stop();
        client_.Disconnect();

    }

};

int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow) {

    DrawingClient client{ hInstance };

    if (!client.Run())
        return EXIT_FAILURE;

    client.Stop();

    return EXIT_SUCCESS;
}