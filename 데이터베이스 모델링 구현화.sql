-- 데이터베이스 선택 또는 생성
CREATE DATABASE IF NOT EXISTS game_db;
USE game_db;

-- 1. 유저 테이블
CREATE TABLE user (
    user_id CHAR(5) PRIMARY KEY,
    nickname VARCHAR(20) NOT NULL UNIQUE,
    level INT DEFAULT 1 CHECK (level >= 1),
    reg_date DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 2. 아이템 테이블
CREATE TABLE item (
    item_id CHAR(5) PRIMARY KEY,
    item_name VARCHAR(30) NOT NULL,
    item_type CHAR(10) DEFAULT '장비',
    price INT CHECK (price >= 0)
);

-- 3. 유저-아이템 보유 관계 테이블
CREATE TABLE user_item (
    user_id CHAR(5),
    item_id CHAR(5),
    owned_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (user_id, item_id),
    FOREIGN KEY (user_id) REFERENCES user(user_id) ON DELETE CASCADE,
    FOREIGN KEY (item_id) REFERENCES item(item_id)
);
