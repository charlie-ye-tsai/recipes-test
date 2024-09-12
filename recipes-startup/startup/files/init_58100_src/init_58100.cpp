#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <linux/gpio.h>

int main(int argc, char **argv)
{
    struct gpiohandle_request req;
    struct gpiohandle_data data;
    char chrdev_name[20];
    int fd, ret;

    // 指定要使用的 gpiochip (可以用 gpioinfo 查詢)
    strcpy(chrdev_name, "/dev/gpiochip8");
    printf("[INFO] Opening %s\n", chrdev_name);

    // 打開對應的 gpiochip 檔案
    fd = open(chrdev_name, O_RDONLY);
    if (fd == -1) {
        ret = -errno;
        fprintf(stderr, "Failed to open %s\n", chrdev_name);
        return ret;
    }

    // 設定我們要控制的結構體
    memset(&req, 0, sizeof(req)); // 清空 struct
    req.lineoffsets[0] = 0; // gpiochip8 0 PI0
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.lines = 1; // 要控制的總數
    strcpy(req.consumer_label, "gpio8_0 PI0");

    // 設定初始值
    data.values[0] = 1;

    // 獲取 gpio 的 handle
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    if (ret == -1) {
        ret = -errno;
        fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n", ret);
        close(fd);
        return ret;
    }

    if (close(fd) == -1) {
        perror("Failed to close GPIO character device file");
    }

    printf("[INFO] GPIO Test Start\n");


    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (ret == -1) {
        ret = -errno;
        fprintf(stderr, "Failed to issue GPIOHANDLE_SET_LINE_VALUES_IOCTL (%d)\n", ret);
        close(req.fd);
        return ret;
    }

    printf("[INFO] Set PI0 to %d\n", data.values[0]);

    // 釋放 handle
    ret = close(req.fd);
    if (ret == -1) {
        perror("Failed to close GPIO LINEHANDLE device file");
        ret = -errno;
    }

    return ret;
}
