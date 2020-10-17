/* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_Delay(1000);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_Delay(1000);

	  // Alternatively
	  /*
	   *
	   * HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	   * HAL_Delay(1000);
	   *
	   *
	   */
  }
  /* USER CODE END 3 */
