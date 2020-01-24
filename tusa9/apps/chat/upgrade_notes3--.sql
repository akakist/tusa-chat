alter table notes add column owner_folder int unsigned not null default 0,add key (owner_folder),
	add column owner_uid int unsigned not null default 0, add key(owner_uid),
	modify column id int unsigned not null default 0, drop primary key, add key(id);  
alter table note_texts add column owner_uid int unsigned not null default 0, add key(owner_uid), drop column uid;
alter table filters_in add column owner_uid int unsigned not null default 0, add key(owner_uid);
alter table filters_out add column owner_uid int unsigned not null default 0, add key(owner_uid);
alter table note_folders modify column id int unsigned not null default 0, drop primary key, add key(id);  
alter table notes add notify_read int unsigned not null default 0; 


