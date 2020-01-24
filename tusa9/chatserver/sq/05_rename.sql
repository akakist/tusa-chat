rename table users to tbl_users;
alter table bans modify column  channel int not null default '0';
alter table channels modify column move_to_channel int not null default '0';
alter table moderators modify channel int not null default 0;
