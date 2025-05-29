show index from member;
select meem_id, mem_name from member;
#pk 없앳다고해서 굳이 데이터페이지를 건들지 않음
#하지만 pk 없으므로 새롭게 insert하거나 하면 맨 끝에 붙을까 아닐까?

select * from member;
desc member;
insert into member values('DOO','둘리',1,'빙하',null,null,120,null);
# 이제 다시 mem_id에 PK를 만들면?
alter table member add primary key(mem_id);
select * from member;