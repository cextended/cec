void concat(std::shared_ptr<Typer> start, std::shared_ptr<Typer> end) {
	std::shared_ptr<Typer> current_end = start;
	while(current_end->respect_typer) {
		current_end = current_end->respect_typer;
	}

	current_end->respect_typer = end;
}
