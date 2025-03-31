# 2048 Game

## Giới thiệu

Đây là một phiên bản của game 2048 được viết bằng ngôn ngữ C++ và sử dụng thư viện SDL để hiển thị đồ họa. Trò chơi có các hiệu ứng mượt mà khi di chuyển và gộp ô số.

## Tính năng

- Hỗ trợ di chuyển các ô số lên, xuống, trái, phải.
- Hiệu ứng hợp nhất khi hai ô số giống nhau gộp lại.
- Hiển thị điểm số và điểm cao nhất.
- Hỗ trợ lưu điểm cao nhất khi thắng.

## Yêu cầu hệ thống

- Hệ điều hành: Windows, Linux, macOS
- Trình biên dịch: g++ hoặc MSVC
- Thư viện:
  - SDL2
  - SDL2_image
  - SDL2_ttf
  - SDL2_mixer

## Cách cài đặt và chạy

1. **Clone repository:**
   ```sh
   git clone https://github.com/yourusername/2048-game.git
   cd 2048-game
   ```
2. **Cài đặt thư viện SDL**
   - Windows: Cài đặt SDL từ trang chủ https://www.libsdl.org/ và đặt thư viện vào thư mục phù hợp.
   - Linux/macOS:
     ```sh
     sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
     ```
3. **Biên dịch và chạy**
   ```sh
   g++ main.cpp -o 2048 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
   ./2048
   ```

## Cách chơi

- Dùng **các phím mũi tên** để di chuyển các ô số.
- Hai ô số giống nhau khi va chạm sẽ gộp lại thành một ô có giá trị gấp đôi.
- Mục tiêu là đạt được ô số **2048**.
- Nếu không còn bước đi hợp lệ, trò chơi kết thúc.

## Đóng góp

Nếu bạn muốn đóng góp cho dự án, hãy **fork repo**, tạo một nhánh mới và gửi pull request.

## Giấy phép

Dự án này được phát hành theo giấy phép MIT. Bạn có thể tự do sử dụng và chỉnh sửa.

---
Cảm ơn bạn đã chơi game 2048! 🎮

