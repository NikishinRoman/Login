#include "server.h"

static QMutex mutex;

Server::Server(int port)
{
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

    for (;;)
    {
        socketPtr socket(new tcp::socket(io_service));
        acceptor.accept(*socket);
        boost::thread t(boost::bind(Session, socket));
    }
}

void Server::Session(socketPtr socket)
{
    try {
        cout << "Request accepted! Processing... ";
        string OkMessage = "Ok";
        char recvBuff[lengthBuf];
        boost::system::error_code error;

        if (socket->read_some(boost::asio::buffer(recvBuff), error) > 0) {
            if (!strcmp(recvBuff, "recognition")) {
                boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
                Recognition(socket);
            }
            else if (!strcmp(recvBuff, "registration")) {
                boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
                Registration(socket);
            }
            else if (!strcmp(recvBuff, "check_user")) {
                boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
                CheckUser(socket);
            }
        }
    }
    catch (exception& e) {
        cerr << "Exception in thread: " << e.what() << endl;
    }
}

void Server::Recognition(socketPtr &socket)
{
    try {
        string OkMessage = "Ok";
        stringstream sock;
        sock << socket;
        char recvBuff[lengthBuf];
        boost::asio::streambuf sb;
        boost::system::error_code error;

        if (socket->read_some(boost::asio::buffer(recvBuff), error) > 0)
            boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));

        string temp_ = string(recvBuff);
        int disp_1 = temp_.find('+');
        int disp_2 = temp_.find('#');

        string parcelSize = string(temp_.begin(), temp_.begin() + disp_1);
        string userName = string(temp_.begin() + disp_1 + 1, temp_.begin() + disp_2);
        string threshold = string(temp_.begin() + disp_2 + 1, temp_.end());

        boost::asio::read(*socket, sb, boost::asio::transfer_exactly(atoi(parcelSize.c_str())), error);

        string receivedData( (std::istreambuf_iterator<char>(&sb)), std::istreambuf_iterator<char>() );

        boost::asio::write(*socket, boost::asio::buffer(RecognitionFace(receivedData, sock.str(), userName, threshold)));

        cout << "Reply sent!" << endl << endl;
    }
    catch (exception& e) {
        cerr << "Exception in thread: " << e.what() << endl;
    }
}

void Server::Registration(socketPtr &socket)
{
    try {
        string OkMessage = "Ok";
        char recvBuff[lengthBuf];
        boost::asio::streambuf sb;
        boost::system::error_code error;

        if (socket->read_some(boost::asio::buffer(recvBuff), error) > 0) {
            if (!strcmp(recvBuff, "recognition_photo_done")) {
                memset(&recvBuff, 0x0, lengthBuf);
                if (socket->read_some(boost::asio::buffer(recvBuff), error) > 0) {  // принимаем имя пользователя
                    string userName = string(recvBuff);

                    cout << endl << "Training started! User: " << userName << endl;

                    mutex.lock();

                    /* Копируем папку с фото в папку для обчуения классификатора */
//                    copyDir(boost::filesystem::path("/home/user/Documents/Tests/openface/RegistrationFace/" + userName),
//                            boost::filesystem::path("/home/user/Documents/Tests/openface/training-images/" + userName));
                    u_int16_t timeout = 10000;
                    QProcess p;
                    string command = "cp -r /home/user/Documents/Tests/openface/RegistrationFace/" + userName +
                            " /home/user/Documents/Tests/openface/training-images/" + userName;
                    QString scriptFile = command.c_str();
                    p.start(scriptFile);
                    p.waitForFinished(timeout);

                    /* Очищаем временные фото для обучения */

                    QString pythonCommand = "rm -rf /home/user/Documents/Tests/openface/aligned-images";
                    p.start(pythonCommand);
                    p.waitForFinished(timeout);

                    /* Запускаем обучение */
                    scriptFile = "/home/user/Documents/Tests/openface/util/align-dlib.py"
                            " /home/user/Documents/Tests/openface/training-images/ align"
                            " outerEyesAndNose /home/user/Documents/Tests/openface/aligned-images/ --size 96";
                    pythonCommand = "python " + scriptFile;
                    p.start(pythonCommand);
                    p.waitForFinished(timeout);

                    command = "/home/user/Documents/Tests/openface/batch-represent/main.lua -outDir"
                            " /home/user/Documents/Tests/openface/generated-embeddings/" + userName + "/"
                            " -data /home/user/Documents/Tests/openface/aligned-images/";
                    scriptFile = command.c_str();
                    p.start(scriptFile);
                    p.waitForFinished(timeout);

                    command = "/home/user/Documents/Tests/openface/demos/classifier.py train"
                            " /home/user/Documents/Tests/openface/generated-embeddings/" + userName + "/";
                    scriptFile = command.c_str();
                    pythonCommand = "python " + scriptFile;
                    p.start(pythonCommand);
                    p.waitForFinished(timeout);

                    command = "rm -rf /home/user/Documents/Tests/openface/training-images/" + userName;
                    pythonCommand = command.c_str();
                    p.start(pythonCommand);
                    p.waitForFinished(timeout);

                    cout << "Training is over! User: " << userName << endl;

                    boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
                    mutex.unlock();
                }
            }
            else {
                boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
                string temp_ = string(recvBuff);
                int disp_1 = temp_.find('+');
                int disp_2 = temp_.find('#');

                string parcelSize = string(temp_.begin(), temp_.begin() + disp_1);
                string userName = string(temp_.begin() + disp_1 + 1, temp_.begin() + disp_2);
                string numberPhoto = string(temp_.begin() + disp_2 + 1, temp_.end());

                boost::asio::read(*socket, sb, boost::asio::transfer_exactly(atoi(parcelSize.c_str())), error);

                string receivedData((std::istreambuf_iterator<char>(&sb)), std::istreambuf_iterator<char>());

                boost::asio::write(*socket, boost::asio::buffer(RegistrationFace(receivedData, userName, numberPhoto)));

                cout << "Photo save!" << endl << endl;
            }
        }

        cout << "Reply sent!" << endl << endl;
    }
    catch (exception& e) {
        cout << "ERROR!!! NOT Reply sent!" << endl << endl;
        cerr << "Exception in thread: " << e.what() << endl;
    }
}

void Server::CheckUser(socketPtr &socket)
{
    try {
        string OkMessage = "Ok";
        string ErrorMessage = "Not";
        char recvBuff[lengthBuf];
        boost::system::error_code error;
        memset(&recvBuff, 0x0, lengthBuf);

        if (socket->read_some(boost::asio::buffer(recvBuff), error) > 0) {  // принимаем имя пользователя
            string userName = string(recvBuff);
            string folder = "/home/user/Documents/Tests/openface/generated-embeddings/" + userName;
            if (QDir(folder.c_str()).exists())
                boost::asio::write(*socket, boost::asio::buffer(OkMessage, OkMessage.length()));
            else
                boost::asio::write(*socket, boost::asio::buffer(ErrorMessage, ErrorMessage.length()));
        }
        cout << "Reply sent!" << endl << endl;
    }
    catch (exception& e) {
        cout << "ERROR!!! NOT Reply sent!" << endl << endl;
        cerr << "Exception in thread: " << e.what() << endl;
    }
}
