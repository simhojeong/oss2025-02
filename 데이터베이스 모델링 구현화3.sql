SELECT u.nickname AS 유저닉네임,
       i.item_name AS 아이템명,
       i.price AS 가격,
       ui.owned_date AS 보유일
FROM user_item ui
JOIN user u ON ui.user_id = u.user_id
JOIN item i ON ui.item_id = i.item_id;
