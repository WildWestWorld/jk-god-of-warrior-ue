#pragma once


namespace Debug
{
	/**
	 * Prints a debug message to the screen and logs it.
	 * @param Msg The message to display and log.
	 * @param Color The color used to display the message on the screen.
	 * @param InKey A unique key for identifying the message (optional).
	 */
	void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1);
	void Print(const FString& FloatTitle, float FloatValueToPrint, int32 InKey = -1,
	           const FColor& Color = FColor::MakeRandomColor());
}
