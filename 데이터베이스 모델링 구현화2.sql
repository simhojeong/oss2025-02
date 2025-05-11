-- 유저
INSERT INTO user VALUES ('U001', '탑장인', 250, NOW());
INSERT INTO user VALUES ('U002', '정글충', 180, NOW());
INSERT INTO user VALUES ('U003', '서폿맛집', 130, NOW());

-- 아이템
INSERT INTO item VALUES ('I001', '삼위일체', '장비', 3300);
INSERT INTO item VALUES ('I002', '광휘의 검', '장비', 1300);
INSERT INTO item VALUES ('I003', '불타는 향로', '서포터', 2300);

-- 유저가 가진 아이템
INSERT INTO user_item VALUES ('U001', 'I001', NOW());
INSERT INTO user_item VALUES ('U001', 'I002', NOW());
INSERT INTO user_item VALUES ('U002', 'I003', NOW());
