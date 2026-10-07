#ifndef ROW_H
#define ROW_H

#include <stddef.h>
#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

// 计算偏移量
// 1. 各个字段的大小（Size）
#define ID_SIZE       sizeof(((Row*)0)->id)
#define USERNAME_SIZE sizeof(((Row*)0)->username)
#define EMAIL_SIZE    sizeof(((Row*)0)->email)

// 2. 各个字段在结构体中的物理偏移量（Offset）
#define ID_OFFSET       offsetof(Row, id)
#define USERNAME_OFFSET offsetof(Row, username)
#define EMAIL_OFFSET    offsetof(Row, email)

// 3. 紧凑排列后的整行记录总大小（ROW_SIZE）
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

// 序列化和反序列化
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);

#endif // ROW_H