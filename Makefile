# Docker操作
d-build:
	docker compose build

d-up:
	docker compose up -d

d-upb:
	docker compose up -d --build

d-down:
	docker compose down	

d-clean:
	docker compose down --rmi all --volumes --remove-orphans
