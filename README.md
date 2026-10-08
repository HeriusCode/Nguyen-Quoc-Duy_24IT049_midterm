Midterm Project
Github: https://github.com/HeriusCode/Nguyen-Quoc-Duy_24IT049_midterm.git
1.	Kiểm tra chạy chương trình cơ bản
./myls
Kiểm tra chương trình có thể khởi động và liệt kê nội dung thư mục hiện tại hay không. Kết quả cho thấy chương trình thực thi bình thường và hiển thị danh sách các file, thư mục.
 
 2.	Kiểm tra -a
./myls -a
Chương trình hiển thị cả file ẩn và các entry . và .. .

4.	Kiểm tra -A
./myls -A
Sử dụng để kiểm tra khả năng hiển thị các entry ẩn nhưng loại trừ . và .. .
 
5.	Kiểm tra -c
./myls -lc test.txt
./myls -tc old.txt middle.txt new.txt
Kết hợp với -t và -l nhằm xác nhận chương trình sử dụng thời gian thay đổi metadata của file theo yêu cầu.
 
6.	Kiểm tra -d
./myls -d testdir
Sử dụng để kiểm tra chương trình có xử lý directory như một file thông thường hay không. 
 
7.	Kiểm tra -F
./myls -F
Xác nhận chương trình có thể thêm ký hiệu tương ứng vào tên file dựa trên loại file.
 
8.	Kiểm tra -f
./myls -f
Xác nhận chương trình hiển thị các entry theo thứ tự filesystem thay vì thực hiện sắp xếp theo tên hoặc các tiêu chí khác.
 
9.	Kiểm tra -h
./myls -lh test2.txt
./myls -sh test2.txt
Kết hợp với -l và -s nhằm xác nhận kích thước file/block được hiển thị ở dạng dễ đọc đối với người dùng.
 
10.	Kiểm tra -i
./myls -i test.txt
Xác nhận chương trình có thể lấy và hiển thị số inode của file thông qua thông tin filesystem.
 
11.	Kiểm tra -k
./myls -sk test.txt
Kết hợp với -s để xác nhận kích thước block được tính và hiển thị theo đơn vị kilobyte.
 
12.	Kiểm tra -l
./myls -l link.txt
Xác nhận chương trình có thể lấy thông tin metadata của file và hiển thị theo dạng chi tiết.
 
13.	Kiểm tra -n
./myls -n test.txt
Xác nhận thông tin owner và group được hiển thị dưới dạng UID/GID số.
 
14.	Kiểm tra -q
./myls -q
Xác nhận các ký tự không thể hiển thị được thay thế bằng ký tự ?.
 
15.	Kiểm tra -R
./myls -R testdir
Kiểm tra bằng một thư mục có chứa thư mục con.
 
16.	Kiểm tra -r
./myls -r
Xác nhận thứ tự kết quả có thể được đảo ngược so với thứ tự sắp xếp mặc định.
 
17.	Kiểm tra -S
./myls -S small.txt medium.txt big.txt
Kiểm tra bằng các file có kích thước khác nhau. Kết quả cho thấy file có kích thước lớn hơn được ưu tiên hiển thị trước.
 
18.	Kiểm tra -s
./myls -s test2.txt
Xác nhận chương trình có thể lấy và hiển thị số block filesystem được sử dụng bởi từng file.
 
19.	Kiểm tra -t
./myls -t old.txt middle.txt new.txt
Xác nhận chương trình có thể sắp xếp file theo thời gian sửa đổi, với file được sửa gần nhất xuất hiện trước.
 
20.	Kiểm tra -u
./myls -tu old.txt middle.txt new.txt
./myls -lu test.txt
Kết hợp với -t và -l nhằm xác nhận chương trình sử dụng access time theo yêu cầu.
 
21.	Kiểm tra -w
./myls -w
Xác nhận tên file được xuất ở dạng raw, giữ nguyên các ký tự thay vì thay thế chúng bằng ký tự ?.
 
22.	Kiểm tra option override
Một số option sẽ override nhau tùy theo option xuất hiện cuối cùng.
-h và -k
./myls -hks test2.txt
./myls -khs test2.txt
 
-l và -n
./myls -ln test2.txt
./myls -nl test2.txt
 
-c và -u
./myls -lcu test.txt
./myls -luc test.txt
 
-q và -w
./myls -qw
 
./myls -wq
 
	Các nhóm option có quan hệ override được kiểm tra bằng cách thay đổi thứ tự xuất hiện của option trong command line. Kết quả được đối chiếu để xác nhận option xuất hiện sau cùng có hiệu lực.

22.	Kiểm tra multiple operands
./myls test2.txt test.txt old.txt
Xác nhận chương trình có thể nhận đồng thời nhiều file và directory, xử lý chúng đúng thứ tự và không xảy ra lỗi khi số lượng operand tăng.
 
23.	Kiểm tra symbolic link
Symbolic link là một loại file đặc biệt. Với -F, symbolic link phải được đánh dấu bằng @; trong long format -l, nếu là symbolic link thì phải hiển thị đích theo dạng target.
./myls link.txt
./myls -F link.txt
./myls -l link.txt
./myls -d link.txt
./myls -F linkdir
 
24.	Kiểm tra long format
./myls -l test2.txt
Long format được kiểm tra bằng option -l. Chương trình phải lấy thông tin metadata từ filesystem và hiển thị đầy đủ quyền truy cập, số hard link, owner, group, kích thước, thời gian và tên file.
 

